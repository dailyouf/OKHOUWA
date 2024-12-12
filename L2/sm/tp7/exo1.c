#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

	
int main(int argc, char * argv[]) {
	
	int i, fd;
	
	unsigned char uc[16];
	
	if (argc == 1) {
		perror("Aucun argument sur la ligne de commande \n");
        	return EXIT_FAILURE;
	}
	
	printf("Nombre et liste des arguments reçus sur la ligne de commande %d \n", argc-1);
	for (int j=1; j<argc; j++) {
		printf("%s \n", argv[j]);
	}
	printf("\n");
	
	fd = open(argv[1], O_RDWR);
	
	if (fd == -1) {
        	perror("Erreur lors de l'ouverture du fichier \n");
        	return EXIT_FAILURE;
    	}
	
	// Lecture et affichage des 16 premiers
	lseek(fd, 0, SEEK_SET);
	
	read(fd, uc, 16);
	
	for (i=0; i<16; i++) {
		printf(" %02x ", uc[i]);
	}
	
	printf("\n");
	
	
	// Lecture et affichage des 16 dernier
	lseek(fd, -16, SEEK_END);
	
	read(fd, uc, 16);
	
	for (i=0; i<16; i++) {
		printf(" %02x ", uc[i]);
	}
	
	printf("\n");
	
	close(fd);
	
	return EXIT_SUCCESS;
} 
