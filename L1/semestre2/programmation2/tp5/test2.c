#include <stdlib.h>
#include <stdio.h>


int main(){

	return EXIT_SUCCESS;
}

int recherche_dichotomique(int tableau[], int taille, int valeur){
	
	int debut=0, fin=taille-1;
	
	while (debut <= fin){
	
		int milieu = debut + (fin - debut) / 2;
	
		if (tableau[milieu] = valeur) return milieu;
		
		if (valeur < tableau[milieu]) fin = milieu - 1;
		
		if (valeur > tableau[milieu]) debut = milieu + 1;
	
	}
	
	return -1;
}

int recherche_dichotomique(int tableau[], int taille, int valeur, debut, fin){
	
	if (debut > fin) return -1;
	
	int milieu milieu = debut + (fin - debut) / 2;
	
	if (tableau[milieu] = valeur) return milieu;
		
	if (valeur < tableau[milieu]) return recherche_dichotomique(tableau, taille, int valeur, debut, milieu-1);
		
	if (valeur > tableau[milieu]) return recherche_dichotomique(tableau, taille, int valeur, milieu+1, fin);

}


int recherche_dichotomique(int tableau[], int taille, int valeur){

	return recherche_dichotomique(tableau, 0, taille-1, taille, valeur);
}
