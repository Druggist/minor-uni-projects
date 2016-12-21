#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
	if(fork() == 0){
		int id = shmget(102, 20, IPC_CREAT|0644);
		char* ptr = shmat(id, 0, 0);
		while(1) {
			strcpy(ptr, "aaaaaaaaaaaaaaaaaaaa");
			printf("%s\r", ptr);
		}
	} else {
		int id = shmget(102, 20, IPC_CREAT|0644);
		char* ptr = shmat(id, 0, 0);
		while(1){
			strcpy(ptr, "bbbbbbbbbbbbbbbbbbbb");
			printf("%s\r", ptr);
		}

	}
	return 0;
}