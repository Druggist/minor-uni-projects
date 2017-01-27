#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void checkSignal(int sig){
	printf("Signal: %d\n", sig);
}

int main(int argc, char *argv[]) {
	for(int i = 0; i < 21; i++)	signal(i,checkSignal);
	sleep(10);
	return 0;
}