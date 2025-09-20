#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>


int main() {

	int fd;
	
	if ((fd = open("lol.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
	
		perror("open: ");
		return EXIT_FAILURE;	
			
	}
	
	
	char * s = "hop !\nplop !\n";
	
	if (write(fd, s, strlen(s)) == -1) {
	
		perror("write: ");
		return EXIT_FAILURE;
	
	}
	
	close(fd);
	
	
	return EXIT_SUCCESS;

}
