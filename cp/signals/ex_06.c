/* TODO
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void sleepFun(int sec){
	alarm(sec);
	pause();
}

int main(int argc, char *argv[]) {
	if(fork() == 0){
		sleep(2);
	} else {
		if(fork() == 0){
			sleep(4);
		} else {
			if(fork() == 0){
				sleep(5);
			} else {
				wait();

			}
		}
	}
	wait();
}
*/