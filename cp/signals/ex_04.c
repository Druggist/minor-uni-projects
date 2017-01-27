#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void sleepFun(int sec){
	alarm(sec);
	pause();
}

void f(){
	return;
}

int main(int argc, char *argv[]) {
	if(argc != 2) return -1;
	signal(SIGALRM,f); 
	sleepFun(atoi(argv[1]));
	return 0;
}