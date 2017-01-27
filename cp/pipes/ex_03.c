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
			if(write(pdesk[1], "Hello", 7) == -1) {
				perror("Writing to pipe");
				exit(1);
			}
			exit(0);
		default: { 
			switch(fork()) {
				case -1: // error creating process
					perror ("Creating process");
					exit(1);
				case 0: // child
					if(write(pdesk[1], "world!", 7) == -1) {
						perror("Writing to pipe");
						exit(1);
					}
					exit(0);
				default: { 
					switch(fork()) {
						case -1: // error creating process
							perror ("Creating process");
							exit(1);
						case 0: {// child
							char buf[1];
							while(read(pdesk[0], buf, 1) > 0) {
								printf("%s \n" , buf);
							}
							exit(0);
						}
						default: { 
							wait();
						}
					}
				}
			}
		}
	}

	return 0;
}