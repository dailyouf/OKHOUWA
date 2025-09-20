#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


#define TAILLE_MAX 100

void exo1();
void exo2();

int main() {

	exo1();
	exo2();
		
	return EXIT_SUCCESS;
}


void exo1() {
	
	int pid = fork();
	
	if (pid == 0) {
		printf("C’est le fils qui parle \n");
		printf("Mon pid est %d \n", getpid());
		printf("Le pid de mon père est %d \n", getppid());
		exit(0);
	}
	
	else {

		wait(NULL);
		printf("C’est le père qui parle \n");
		printf("Le pid de mon fils est %d \n", pid);
		printf("Le pid du grand-père de mon fils, donc mon père, est %d \n", getppid());
	}
}

void exo2() {
	
	char path[TAILLE_MAX];
	int pid;
	
	do {
		printf("Veuillez entrer le path du répertoire à lister ou q pour quitter: ");
		scanf("%s", path);
		
		if (path[0] == 'q' && path[1] == '\0') {
			break;
		}
		
		pid = fork();
		
		if (pid == 0) {
			execl("/bin/ls", "ls", path, NULL);
		}
		
		// Si on veut executer la deuxieme version il faut compiler en ajoutant -DV2
		#ifdef V2
		if (pid != wait(NULL)) {
			printf("il y'a eu une erreur ... \n");
			break;
		}
		#endif
		printf("Fils %d a terminé son exécution \n", pid);

		
	}while(1);
	

}
