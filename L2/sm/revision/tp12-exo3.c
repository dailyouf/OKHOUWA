#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {

	int fd[2], pid, value;
	
	pipe(fd);


	if ((pid = fork()) == 0) {
		
		int nb_paires=0, nb_impaires=0;
		
		close(fd[1]);
		
		while (read(fd[0], &value, sizeof(int)) > 0) {
		
			if (value % 2 == 0) {
				nb_paires++;
			}
			else {
				nb_impaires++;
			}
				
		
		}
		
		printf("il y'a eu %d valeurs paires et %d valeurs impaires \n", nb_paires, nb_impaires);
	
		close(fd[0]);
		exit(0);
		
	} else {
		
		if ((pid = fork()) == 0) {
			
			close(fd[0]);
			
			printf("Veuillez entrer les valeurs positives lire: \n");
			
			do {
				scanf("%d", &value);
				
				if (value < 0) {
					break;
				}
				
				write(fd[1], &value, sizeof(int));
				
				
			} while(1);
			
			close(fd[1]);
			exit(0);

		}		
	
		else {
			
			close(fd[0]);
			close(fd[1]);
			
			wait(NULL);
			wait(NULL);	
			
		}
		
	}	

	return EXIT_SUCCESS;
}
