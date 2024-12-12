#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

void renverser_liste(struct liste * l);

void partionner_liste_pivot(struct liste * l, float p);

void trier_liste_insertion(struct liste * l);

int main(){
	
	struct liste * my_list = nouvelle_liste();


	return EXIT_SUCCESS;
}

void renverser_liste(struct liste * l) {

	struct liste * l2 = nouvelle_liste();
	
	while (!est_vide_liste(l)) {
		ajouter_maillon_debut_liste(l2, extraire_maillon_debut_liste(l));		
	}
	
	*l = *l2;

	free(l2);
	
}

void partionner_liste_pivot(struct liste * l, float p) {
	
	struct liste * l2 = nouvelle_liste();
	
	struct maillon * m;
	
	while (!est_vide_liste(l)) {
		
		m = extraire_maillon_debut_liste(l);
		
		if less(m->valeur, p) {	
			ajouter_maillon_debut_liste(l2, m);	
		}
		else {
			ajouter_maillon_fin_liste(l2, m);
		}
		
		m=NULL;
	}
	
	*l = *l2;

	free(l2);
}


void trier_liste_insertion(struct liste * l) {
	
	int i, j=0;
	
	struct liste * l2 = nouvelle_liste();
	
	struct maillon * m;
	struct maillon * i;
	
	while (!est_vide_liste(l)) {
		
		m = extraire_maillon_debut_liste(l);
	
		for (i=j+1; i<l2->longueur; i++) {
			
			if (m->valeur > acceder_pos_liste(const struct liste *l, unsigned pos))
		
		}
		
		
		m=NULL;
	}
	
	*l = *l2;

	free(l2);
}


