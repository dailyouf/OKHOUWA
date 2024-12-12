#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFERSIZE 1024

int main(int argc, char * argv[]) {
	
	char uc[BUFFERSIZE];
	int lu, i, fd;	
	
	if (argc == 1) {
		while ((lu=read(0, uc, BUFFERSIZE)) > 0) {
			write(1, uc, lu);
		}
	}
	
	else {
		
		for (i=1; i<argc; i++) {
			
			fd = open(argv[i], O_RDONLY);
			
			printf("**** LECTURE DU FICHIER %s ***************\n\n", argv[i]);
			
			while ((lu=read(fd, uc, BUFFERSIZE)) > 0) {
				write(1, uc, lu);
			}
			
			printf("\n**** FIN DE LECTURE DU FICHIER %s ***************\n\n\n", argv[i]);
			
			close(fd);
			
		}
	
	}
	
	return EXIT_SUCCESS;

}
