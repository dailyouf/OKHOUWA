#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(){
	
	int choix;
	
	
	do{
		printf("Veuillez faire un choix entre les proposition suivantes :  \n (1)tester si un entier est premier, (2) deviner un nombre ou (0) quitter.");		
		scanf(" %d \n", &choix);		
		
		if (choix == 0){
			printf("FIN DU PROGRAMME \n");
			break;
		}	
		else if (choix == 1){
			printf("premier : non disponible \n");
		}else if (choix == 2){
			printf("deviner un nombre : non disponible \n");
		}else {
			printf("deviner un nombre : non disponible \n");
			continue;
		}
		
	}while (TRUE);






	return EXIT_SUCCESS;

}
