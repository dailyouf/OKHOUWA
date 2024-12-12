#include <stdlib.h>
#include <stdio.h>

int sommes_chiffres(unsigned n);

int main(){

	printf("%d \n", sommes_chiffres(375));
	
	return EXIT_SUCCESS;	
	
}

int sommes_chiffres(unsigned n){

	if (n==0) return 0;
	
	return (n % 10) + sommes_chiffres(n / 10);
	
}
