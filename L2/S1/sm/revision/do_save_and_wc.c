#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) {
	
	int pid;
	int fd;	
		
	if (argc != 3) {
		printf("Nb d'arguments non correct \n");
		exit(1);
	}
	
	if ((fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IREAD | S_IWRITE) == -1)) {
		printf("Erreur lors de l'ouverture du output \n");
		exit(1);
	}
	
	if ((pid=fork()) == -1) {
		printf("Echec lors du fork \n");
		exit(1);
	}
	
	if (pid == 0) {
		dup2(fd, 1);
		execl(argv[1], argv[1], NULL);
	}
	
	wait(NULL);
	
	execlp("wc", argv[2], NULL);

	
	return EXIT_SUCCESS;
}
