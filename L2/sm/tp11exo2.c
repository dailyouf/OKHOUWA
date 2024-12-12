#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int NSIGINT=0;

void sighand(int sig);

int main() {
	
	printf("Pid: %d \n", getpid());
	
	signal(SIGINT, sighand);
	
	while(1) {
		sleep(1);
	}
	
	
	return EXIT_SUCCESS;

}

void sighand(int sig) {
	
	if (NSIGINT >= 5) {
		printf("\n");
		exit(1);
	}
	
	printf("Appel %d à SIGINT\n", ++NSIGINT);

		
}
