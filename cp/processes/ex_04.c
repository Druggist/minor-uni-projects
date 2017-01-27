#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("Poczatek\n");
	if(fork() == 0){
		execlp("ls", "ls", NULL, NULL);
		exit(1);
	}
	wait();
	printf("Koniec\n");
	return 0;
}