#include <stdlib.h>
#include <stdio.h>
#include "date.h"
#include "individu.h"
#include "laureat.h"
#include <string.h>


int main(int argc, char ** argv){

	int i, taille;
	
	if (argc != 3) {
		fprintf(stderr, "nombre d'argument insufisant \n");
		exit(1);	
	}
	
	struct laureat_Turing ** tab = init_tab_fichier(argv[1], &taille);
	
	for (i=0; i<taille; i++) {
		afficher_individu(tab[i]->laureat);
		printf("\t [%d]", tab[i]->annee_prix);
		printf("\n");
		
	}
	
	printf("\n");
	
	afficher_annees_mult(tab, taille, 1970, 2010);

	printf("\n");	
		

	printf("le nb pays hors États-Unis est: %d \n", reorganiser_tab_pays(tab, taille, "États-Unis"));
	
	for (i=0; i<taille; i++) {
		afficher_individu(tab[i]->laureat);
		printf("\t [%d]", tab[i]->annee_prix);
		printf("\n");
		
	}
	printf("\n");
	
	
	
	tab = oter_tab_age_laureat(tab, &taille, 50);
	
	for (i=0; i<taille; i++) {
		afficher_individu(tab[i]->laureat);
		printf("\t [%d]", tab[i]->annee_prix);
		printf("\n");
		
	}
	printf("\n");	
	
	
	
	trier_tab_age_laureat(tab, taille);
	
	for (i=0; i<taille; i++) {
		afficher_individu(tab[i]->laureat);
		printf("\t [%d]", tab[i]->annee_prix);
		printf("\n");
		
	}
	printf("\n\n");	
	
	sauv_tab_fichier(argv[2], tab, &taille);
		
	return EXIT_SUCCESS;
}


