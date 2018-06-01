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
bool isShipInQueue(std::vector<Queue> queue, int shipId);
void removeShipFromQueue(Canal *canals, int shipId, int canalId);
void addShipToQueue(Canal *canals, int shipId, int canalId, int timestamp);
int getBestCanal(Canal *canals, int shipId, int direction);

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

bool isShipInQueue(std::vector<Queue> queue, int shipId) {
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