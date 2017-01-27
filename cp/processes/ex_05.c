#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("--------Poczatek listy--------\n");
	if(fork() == 0){
		execlp("ps", "ps", "-o", "comm=");
		exit(1);
	}
	wait();
	printf("--------Koniec listy--------\n");
	return 0;
}