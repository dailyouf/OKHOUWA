#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER 1024

int main(int argc, char ** argv) {

	if (argc != 2) {
		printf("Veuillez entrer le nombre correct d'aguments ...\n");
		return EXIT_FAILURE;
	}
	
	
	int fd = open(argv[1], O_RDONLY);
	
	int fd2;
	
	int fin = lseek(0, SEEK_END);
	
	int i, taille=0, lu, n;
	
	unsigned char uc[BUFFER];


	n = atoi(argv[2]);
	
	while (arg[1][taille++] != '\0');
	
	taille--;	
	
	char * new = malloc(taille + 2);
	
	for (i=0; i<taille; i++) {
		new[i] = argv[1][i];
	}
	
	
	lseek(0, SEEK_SET);
	
	fin %= n;
	
	for (i=0; i<fin; i++) {	
		
		new[taille] = '.';
		new[taille + 1] = i + '0';
		new[taille + 2] = '\0';
		
		fd2 = open(new, O_CREAT | S_IWRITE);
		
		lu = read(fd, uc, BUFFER);
		
		lseek(fd, -lu, SEEK_CUR);
		
		write(fd2, uc, lu);
		
		close(fd2);
	
	}
	
	close(fd);
	
	
	return EXIT_SUCCESS;


}
