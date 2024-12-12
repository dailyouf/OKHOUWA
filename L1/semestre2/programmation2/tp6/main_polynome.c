#include<stdlib.h>
#include<stdio.h>
#include "polynome.h"

int main(int argc, char ** argv){

	int dp, dq;
	struct polynome * p, * q;
	
	if (argc != 3) {
		printf("Nomre de caractères insuffisant \n");
		exit(1);
	}
	
	dp = atoi(argv[1]);
	dq = atoi(argv[2]);
	
	if ((dp < -1) || (dq < -1)) {
		printf("degré trop petits \n");
		exit(1);
	}
	
	p = creer_polynome(dp);
	q = creer_polynome(dq);
	
	afficher_poly(p);
	
	afficher_poly(p);
	
	afficher_poly(multiplier_polynome(p, q));
	
	evaluer_poly(p);
	
	detruire_polynome(&p);
	detruire_polynome(&q);
	
	
	return EXIT_SUCCESS;
}
