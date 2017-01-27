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
	int i = 0;
	while(1) {
	    if (*ptr > 0) {
			struct sembuf sb;
			sb.sem_num = 0;
			sb.sem_op = -1;
			sb.sem_flg = 0;
			semop(semid, &sb, 1);
	    	i += 1;
	    	*ptr -= 1;
			sb.sem_op = 1;
			semop(semid, &sb, 1);
	    }
	    printf("Heheheheh honeeey: %d\r", i);
	}
	return 0;
}