#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int pdesk[2];

	if (pipe(pdesk) == -1) {
		perror("Creating pipe");
		exit(1);
	}

	switch(fork()) {
		case -1: // error creating process
			perror ("Creating process");
			exit(1);
		case 0: // child
			if(write(pdesk[1], "Hello!", 7) == -1) {
				perror("Writing to pipe");
				exit(1);
			}
			exit(0);
		default: { 
			char buf[10];
			if(read(pdesk[0], buf, 10) == -1) {
				perror ("Reading from pipe");
				exit (1) ;
			}
			printf(" Read from pipe: %s \n" , buf);
		}
	}
	return 0;
}