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
int getQueuePosition(std::vector<Ship> queue, int shipId);
int getBestCanal(Canal *canals, int shipId, int direction);
void addShipToQueue(Canal *canals, int shipId, int canalId, int direction, int timestamp);
void removeShipFromQueue(Canal *canals, int shipId, int canalId);
void useCanal(Canal *canals, int canal, int tid, int shipsCount, std::vector<int> queued, 
	pthread_mutex_t *mutexCanals, int *clock, int desiredDirection);

void sendMsg(int dest, int tag, int shipId, int type, int timestamp, int canalId, int direction);
Msg receiveMsg(int tag);
void createCustomMessageType();

ThreadParams* createThreadParams(int tid, int shipsCount, int *clock, Canal *canals, bool *isRunning, bool *allQueued,
	pthread_mutex_t *mutexCanals, pthread_cond_t *changeCondition);
void* listenerThread(void *thread);
void mainThread(int tid, int shipsCount, int *clock, Canal *canals, bool *isRunning, bool *allQueued,
	pthread_mutex_t *mutexCanals, pthread_cond_t *changeCondition);

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

int getQueuePosition(std::vector<Ship> queue, int shipId) {
	for(int i = 0; i < queue.size(); i++){
		if(queue[i].shipId == shipId) return i;
	}
	return -1;
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

void useCanal(Canal *canals, int canal, int tid, int shipsCount, std::vector<int> queued, 
	pthread_mutex_t *mutexCanals, int *clock, int desiredDirection) {
	pthread_mutex_lock(mutexCanals);
	*clock += 1;
	pthread_mutex_unlock(mutexCanals);
	for(int i = 0; i < queued.size(); i++) {
		if(queued[i] != canal) {
				pthread_mutex_lock(mutexCanals);
				removeShipFromQueue(canals, tid, queued[i]);
				pthread_mutex_unlock(mutexCanals);
			for(int j = 0; i < shipsCount; j++) {
				if(j != tid) {
					sendMsg(j, MSG_TAG, tid, REL_MSG, *clock, queued[i], desiredDirection);
				}
			}
		}						
	}
	
	sleep(rand() % (CANALS_TIME_MAX - CANALS_TIME_MIN) + CANALS_TIME_MIN);
	
	pthread_mutex_lock(mutexCanals);
	*clock += 1;
	removeShipFromQueue(canals, tid, canal);
	pthread_mutex_unlock(mutexCanals);
	for(int i = 0; i < shipsCount; i++) {
		if(i != tid) {
			sendMsg(i, MSG_TAG, tid, REL_MSG, *clock, canal, desiredDirection);
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

void mainThread(int tid, int shipsCount, int *clock, Canal *canals, bool *isRunning, bool *allQueued,
	pthread_mutex_t *mutexCanals, pthread_cond_t *changeCondition) {
	std::vector<int> queued;
	int desiredDirection = rand() % 2 + 1;
	while(*isRunning) {
		if(queued.size() > 0) {
			for(int i = 0; i < queued.size(); i++) {
			    pthread_mutex_lock(mutexCanals);
				int shipPos = getQueuePosition(canals[queued[i]].queue, tid);
				pthread_mutex_unlock(mutexCanals);
				if(shipPos >= 0 && shipPos < canals[queued[i]].capacity) {
					useCanal(canals, queued[i], tid, shipsCount, queued, mutexCanals, 
							clock, desiredDirection);
					queued.clear();
					desiredDirection = (desiredDirection == 2) ? 1 : 2;
					break;
				}
			}
		}
		if(queued.size() < shipsCount) {
			pthread_mutex_lock(mutexCanals);
			int canal = getBestCanal(canals, tid, desiredDirection);
			int currentClock = *clock + 1;
			pthread_mutex_unlock(mutexCanals);
			if(canal >= 0) {
				pthread_mutex_lock(mutexCanals);
				addShipToQueue(canals, tid, canal, desiredDirection, currentClock);
				*clock += 1;
				pthread_mutex_unlock(mutexCanals);
				queued.push_back(canal);
				for(int i = 0; i < shipsCount; i++) {
					if(i != tid) {
						sendMsg(i, MSG_TAG, tid, REQ_MSG, currentClock, canal, desiredDirection);
						Msg msg = receiveMsg(OK_TAG);
						while(msg.timestamp <= currentClock) {
							sendMsg(i, MSG_TAG, tid, REQ_MSG, currentClock, canal, desiredDirection);
							msg = receiveMsg(OK_TAG);
						}
						pthread_mutex_lock(mutexCanals);
						if(msg.timestamp + 1 > *clock) *clock = msg.timestamp + 1;
						pthread_mutex_unlock(mutexCanals);
					}
				}

				pthread_mutex_lock(mutexCanals);
				int shipPos = getQueuePosition(canals[canal].queue, tid);
				pthread_mutex_unlock(mutexCanals);
				if(shipPos >= 0 && shipPos < canals[canal].capacity) {
					useCanal(canals, canal, tid, shipsCount, queued, mutexCanals, 
							clock, desiredDirection);
					queued.clear();
					desiredDirection = (desiredDirection == 2) ? 1 : 2;
				}
			}
		} else {
			pthread_mutex_lock(mutexCanals);
			*allQueued = true;
			while(*allQueued) {
				pthread_cond_wait(changeCondition, mutexCanals);
			}
			pthread_mutex_unlock(mutexCanals);
		}
	}
}