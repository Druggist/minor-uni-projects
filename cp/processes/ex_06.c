/* TODO

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	pid_t p = fork();

    if (p != 0) 
    {
        waitpid(p, NULL, 0); 
        sleep(1); 
        pause(); 
        printf("1. PID: %d PPID %d \n", getpid(), getppid());
    }
    else
    {
        sleep(3); 
    }

	return 0;
}
*/