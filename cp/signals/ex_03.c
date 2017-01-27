#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
	if(argc != 2) return -1;
	if(fork() != 0){
		alarm(atoi(argv[1]));
		pause();
		printf("Alert!\n");
		exit(0);
	}
	// More instructions
	return 0;
}