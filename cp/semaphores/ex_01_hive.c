#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char *argv[]) {
	int id = shmget(102, 20, IPC_CREAT|0644);
	int* ptr = shmat(id, 0, 0);
	int semid = semget(1234, 1, IPC_CREAT|0644);
	if(semid<0) return 1;
	if(semctl(semid, 0, SETVAL, 1) == -1) return 1;
	*ptr = 0;
	while(1) {
	   	printf("Honeeey: %d\r", *ptr);
	}
	return 0;
}