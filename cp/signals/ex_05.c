#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void sleepFun(int sec){
	alarm(sec);
	pause();
}

int main(int argc, char *argv[]) {
	if(argc != 2) return -1;
	if(atoi(argv[1]) == 0) signal(SIGCLD,SIG_DFL); 
	else signal(SIGCLD,SIG_IGN); 
	if(fork() == 0){
		sleep(2);
	}
	sleep(5);
}