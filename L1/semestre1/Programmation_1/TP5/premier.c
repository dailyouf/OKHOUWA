#include <stdlib.h>
#include <stdio.h>

#define TRUE 1;
#define FALSE 0;

int si_premier(int nb){
	int i, res=TRUE;
	for (i=1; i < nb; i++){
		if (nb % i == 0){
			res = FALSE;
			break;
		}
	}
	return res;
}

int main(){

	int nb;

	printf("Entrez votre nombre à tester: ");
	scanf("%d \n", &nb);
	
	if (si_premier(nb)){
		printf("Le nombre est premier");
	}else{
		printf("Le nombre n'est pas premier");
	}
	

	return EXIT_SUCCESS;

}
