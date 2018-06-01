#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <vector>
#include "config.h"

MPI_Datatype MPI_MESSAGE;

void init(int tid, Canal *canals);
bool isShipInQueue(std::vector<Ship> queue, int shipId);
int getBestCanal(Canal *canals, int shipId, int direction);
void addShipToQueue(Canal *canals, int shipId, int canalId, int direction, int timestamp);
void removeShipFromQueue(Canal *canals, int shipId, int canalId);

void sendMsg(int dest, int tag, int shipId, int type, int timestamp, int canalId, int direction);
Msg receiveMsg(int tag);
void createCustomMessageType();
ThreadParams* createThreadParams(int tid, int shipsCount, int *clock, Canal *canals, bool *isRunning, bool *allQueued,
	pthread_mutex_t *mutexCanals, pthread_cond_t *changeCondition);
void* listenerThread(void *thread);

int main(int argc,char **argv) {
	int tid, shipsCount, providedThreads;
	int *clock = new int;
	Canal *canals = new Canal[CANALS_COUNT];
	*clock = 0;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &providedThreads);
	if (providedThreads < MPI_THREAD_MULTIPLE) {
		printf("ERROR: The MPI library does not have full thread support\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	MPI_Comm_size(MPI_COMM_WORLD, &shipsCount);
	createCustomMessageType();
	MPI_Comm_rank(MPI_COMM_WORLD, &tid);
	init(tid, canals);

	pthread_mutex_t *mutexCanals = new pthread_mutex_t;
	pthread_attr_t *attr = new pthread_attr_t;
	pthread_t *thread = new pthread_t;
	pthread_cond_t *changeCondition = new pthread_cond_t;
	bool *isRunning = new bool;
	bool *allQueued = new bool;
	pthread_mutex_init(mutexCanals, NULL);
	pthread_attr_init(attr);
	pthread_attr_setdetachstate(attr, PTHREAD_CREATE_JOINABLE);
	pthread_cond_init(changeCondition, NULL);
	*isRunning = true;
	ThreadParams *params = createThreadParams(tid, shipsCount, clock, canals, isRunning, allQueued, mutexCanals, changeCondition);
	
	int err = pthread_create(thread, attr, listenerThread, (void *)params);
	if (err){
		fprintf(stderr,"ERROR Pthread_create: %d\n", err);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	/*TODO: RUN MAIN THREAD*/

	MPI_Type_free(&MPI_MESSAGE);
	MPI_Finalize();
	pthread_join(*thread, NULL);
	pthread_attr_destroy(attr);
	pthread_mutex_destroy(mutexCanals);
	pthread_cond_destroy(changeCondition);
	delete clock;
	delete params;
	delete [] canals;
	delete mutexCanals;
	delete attr;
	delete thread;
	delete changeCondition;
	delete isRunning;
	delete allQueued;
	pthread_exit(NULL);
}

void init(int tid, Canal *canals){
	srand(time(NULL));
	for (int i = 0; i < CANALS_COUNT; i++) {
		canals[i].direction = 0;
		int capacity;
		if(tid == ROOT){
			capacity = (rand() % (CANALS_CAPACITY_MAX - CANALS_CAPACITY_MIN) + CANALS_CAPACITY_MIN);
			printf("Canal %d\tcapacity: %d\n", i, capacity);
		}
		MPI_Bcast(&capacity, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
		canals[i].capacity = capacity;
	}
	MPI_Barrier(MPI_COMM_WORLD);
}

bool isShipInQueue(std::vector<Ship> queue, int shipId) {
	for(int i = 0; i < queue.size(); i++){
		if(queue[i].shipId == shipId) return true;
	}
	return false;
}

int getBestCanal(Canal *canals, int shipId, int direction) {
	int emptyCanal = -1;
	int fullCanal = -1;
	for(int i = 0; i < CANALS_COUNT; i++){
		if(!isShipInQueue(canals[i].queue, shipId)) {
			if(canals[i].direction == direction){
				if(canals[i].queue.size() < canals[i].capacity) return i;
				else fullCanal = i;
			} else if(canals[i].direction == 0) emptyCanal = i;
		}
	}
	return (emptyCanal != -1) ? emptyCanal : fullCanal;
}

void addShipToQueue(Canal *canals, int shipId, int canalId, int direction, int timestamp) {
	Ship ship;
	ship.shipId = shipId;
	ship.timestamp = timestamp;

	if(canals[canalId].queue.size() <= 0) {
		canals[canalId].direction = direction;
		canals[canalId].queue.push_back(ship);
		return;
	} else if(isShipInQueue(canals[canalId].queue, shipId)) return;

	for(int i = 0; i < canals[canalId].queue.size(); i++) {
		if(canals[canalId].queue[i].timestamp >= timestamp) {
			if(canals[canalId].queue[i].timestamp == timestamp && canals[canalId].queue[i].shipId < shipId) continue;
			canals[canalId].queue.insert(canals[canalId].queue.begin() + i, ship);
			return;
		}
	}
	canals[canalId].queue.push_back(ship);
}

void removeShipFromQueue(Canal *canals, int shipId, int canalId) {
	for(int i = 0; i < canals[canalId].queue.size(); i++) {
		if(canals[canalId].queue[i].shipId == shipId) {
			canals[canalId].queue.erase(canals[canalId].queue.begin() + i);
			if(canals[canalId].queue.size() <= 0) canals[canalId].direction = 0;
			return;
		}
	}
}

void sendMsg(int dest, int tag, int shipId, int type, int timestamp, int canalId, int direction) {
   Msg msg;
   msg.shipId = shipId;
   msg.type = type;
   msg.timestamp = timestamp;
   msg.canalId = canalId;
   msg.direction = direction;
   MPI_Send(&msg, 1, MPI_MESSAGE, dest, tag, MPI_COMM_WORLD);
}

Msg receiveMsg(int tag){
   Msg msg;
   MPI_Status status;
   MPI_Recv(&msg, 1, MPI_MESSAGE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
   printf("RECEIVED: Ship id:%d Type:%d Timestamp:%d Canal id:%d Direction%d\n", 
				msg.shipId, msg.type, msg.timestamp, msg.canalId, msg.direction);
   return msg;
}

void createCustomMessageType(){
   int blocklengths[5] = {1,1,1,1,1};
   MPI_Datatype types[5] = {MPI_INT,MPI_INT,MPI_INT,MPI_INT,MPI_INT};
   MPI_Aint offsets[5];
   offsets[0] = offsetof(struct Message, shipId);
   offsets[1] = offsetof(struct Message, canalId);
   offsets[2] = offsetof(struct Message, direction);
   offsets[3] = offsetof(struct Message, timestamp);
   offsets[4] = offsetof(struct Message, type);

   MPI_Type_create_struct(5, blocklengths, offsets, types, &MPI_MESSAGE);
   MPI_Type_commit(&MPI_MESSAGE);
}

ThreadParams* createThreadParams(int tid, int shipsCount, int *clock, Canal *canals, bool *isRunning, bool *allQueued,
	pthread_mutex_t *mutexCanals, pthread_cond_t *changeCondition) {
	ThreadParams* params = new ThreadParams;
	params->tid = tid;
	params->shipsCount = shipsCount;
	params->clock = clock;
	params->canals = canals;
	params->isRunning = isRunning;
	params->allQueued = allQueued;
	params->mutexCanals = mutexCanals;
	params->changeCondition = changeCondition;
	return params;
}


void* listenerThread(void *thread) {
	ThreadParams *params = (ThreadParams*) thread;
	int tid = params->tid;
	int shipsCount = params->shipsCount;
	int *clock = params->clock;
	Canal *canals = params->canals;
	bool *isRunning = params->isRunning;
	bool *allQueued = params->allQueued;
	pthread_mutex_t *mutexCanals = params->mutexCanals;
	pthread_cond_t *changeCondition = params->changeCondition;

	while(*isRunning) {
		Msg msg = receiveMsg(MSG_TAG);

		switch (msg.type) {
			case REQ_MSG:
				pthread_mutex_lock(mutexCanals);
				addShipToQueue(canals, msg.shipId, msg.canalId, msg.direction, msg.timestamp);
				if(msg.timestamp + 1 > *clock) *clock = msg.timestamp + 1;
				pthread_mutex_unlock(mutexCanals);
				sendMsg(msg.shipId, OK_TAG, tid, OK_MSG, *clock, 0, 0);
				break;
			case REL_MSG:
				pthread_mutex_lock(mutexCanals);
				removeShipFromQueue(canals, msg.shipId, msg.canalId);
				if(msg.timestamp + 1 > *clock) *clock = msg.timestamp + 1;
				*allQueued = false;
				pthread_cond_signal(changeCondition);
				pthread_mutex_unlock(mutexCanals);
				break;
		}
	}
	pthread_exit(NULL);
}