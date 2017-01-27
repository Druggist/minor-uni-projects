#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("1. PID: %d PPID %d \n", getpid(), getppid());
	if (fork()==0) {
		printf("PID: %d PPID %d \n", getpid(), getppid());
		if (fork()==0) {
			printf("PID: %d PPID %d \n", getpid(), getppid());
			exit(1);
		}
		exit(1);
	}
	if (fork()==0) {
		printf("PID: %d PPID %d \n", getpid(), getppid());
		if (fork()==0) {
			printf("PID: %d PPID %d \n", getpid(), getppid());
			exit(1);
		}
		exit(1);
	}
	wait();
	return 0;
}