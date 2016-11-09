#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("Poczatek\n");
	fork();
	printf("Koniec\n");
	return 0;
}