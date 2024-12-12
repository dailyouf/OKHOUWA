#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NB_MAX 100

int main(){

	int nb, choix;
	
	srand(time(NULL));
	
	nb = rand() % (NB_MAX + 1);
	
	printf(" %d \n", nb);
	
	do {
		scanf(" %d", &choix);
		
		if (nb < choix){
			printf("Plus petit \n");	
		}
		if (nb > choix){
			printf("Plus grand \n");
		}
	
	}
	while (choix != nb);
	
	printf("Félecitation \n");

	
	
	
	
	return EXIT_SUCCESS;


}


