#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
	int id = shmget(102, 20, IPC_CREAT|0644);
	int* ptr = shmat(id, 0, 0);
	int i = 0;
	while(1) {
	    if (*ptr > 0) {
	    	i += 1;
	    	*ptr -= 1;
	    }
	    printf("Heheheheh honeeey: %d\r", i);
	}
	return 0;
}