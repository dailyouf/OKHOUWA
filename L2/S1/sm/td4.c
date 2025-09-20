#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 1024

void exo2(int fin, int fout);

void exo3(char * argv[]);

void exo4(char * argv[]);

int main(int argc, char * argv[]) {
		
	

	// exo2(0, 1);

	// exo3(argv);

	exo4(argv);
	
	
	
	return EXIT_SUCCESS;	
}


void exo2(int fin, int fout) {

	unsigned char string[BUFSIZE];
	int j;
		
	while (string[0] != 'q' && (j = read(fin, string, BUFSIZE))>0) {
		write(fout, string, j);
	}
}



void exo3(char * argv[]) {

	int fd = open(argv[1], O_RDWR);
	
	unsigned char buffer[BUFSIZE];
	unsigned char c;
	
	int i, j;
		
	while ((j = read(fd, buffer, BUFSIZE))>0) {
		for (i=0; i+1<j; i+=2) {
			c = buffer[i + 1];
			buffer[i + 1] = buffer[i];
			buffer[i] = c;
		}
		lseek(fd, -j, SEEK_CUR);
		write(fd, buffer, j);	
	}
	
	close(fd);
	
}


void exo4(char * argv[]) {

	// Voir exo2 du tp7
	
	continue;


	/*
	int fd = open(argv[1], O_RDWR);
	
	int j, i = lseek(fd, 0, SEEK_END);
	unsigned char buffer[BUFSIZE];
	
	lseek(fd, 0, SEEK_SET);

	while ((j = read(fd, buffer, i)))
	
	
	close(fd);
	
	
	*/


}
