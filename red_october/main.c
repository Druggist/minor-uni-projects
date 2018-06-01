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

void init(int tid, Canal *canals);
bool isShipInQueue(std::vector<Ship> queue, int shipId);
int getBestCanal(Canal *canals, int shipId, int direction);
void addShipToQueue(Canal *canals, int shipId, int canalId, int direction, int timestamp);
void removeShipFromQueue(Canal *canals, int shipId, int canalId);

void sendMsg(int dest, int tag, int shipId, int type, int timestamp, int canalId = 0, int direction = 0);
Msg receiveMsg(int tag);

int main(int argc,char **argv) {
	
	return 0;
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
	    if(!isShipInQueue(canals[i].queue)) {
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
	} else if(isShipInQueue(canals[canalId].queue)) return;

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

void sendMsg(int dest, int tag, int shipId, int type, int timestamp, int canalId = 0, int direction = 0) {
   Msg msg;
   msg.shipId = shipId;
   msg.type = type;
   msg.timestamp = timestamp;
   msg.canalId = canalId;
   msg.direction = direction;
   MPI_Send(&msg, 1, mpi_message_type, dest, tag, MPI_COMM_WORLD);
}

Msg receiveMsg(int tag){
   Msg msg;
   MPI_Status status;
   MPI_Recv(&msg, 1, mpi_message_type, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
   printf("RECEIVED: Ship id:%d Type:%d Timestamp:%d Canal id:%d Direction%d\n", 
   				msg.shipId, msg.type, msg.timestamp, msg.canalId, msg.direction);
   return msg;
}