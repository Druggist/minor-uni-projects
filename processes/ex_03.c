#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("Poczatek\n");
	execlp("ls", "ls", NULL, NULL);
	printf("Koniec\n");
	return 0;
}