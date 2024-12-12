#include <stdio.h>
#include <stdlib.h>

int main (){

	int n, i, c, s;

	printf("Entrez un nombre positif: ");
	scanf("%d", &n);
	
	s = 0;
	
	for (i=0; i <= n; i++){
		c = i * i ;
		s = s + c ;
	}
	
	printf("La somme des carres des %d premiers entiers est %d \n", n, s) ;
	
	
	return EXIT_SUCCESS; 
	
}

