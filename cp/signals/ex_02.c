#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void (*f)();

int main(int argc, char *argv[]) {
	f = signal(SIGINT,SIG_IGN); 
	sleep(10);
	return 0;
}