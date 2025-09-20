#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


void sighand(int sig);

int main() {
	
	int i;
	
	printf("Pid: %d \n", getpid());
	
	for (i=0; i<NSIG; i++) {
		signal(i, sighand);
	}
	
	while(1) {
		sleep(1);
	}
	
	
	return EXIT_SUCCESS;

}

void sighand(int sig) {
	
	printf("Signal reçu: %d \n", sig);
		
}
