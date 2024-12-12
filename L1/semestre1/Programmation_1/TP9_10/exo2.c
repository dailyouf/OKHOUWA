#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VRAI 1
#define FAUX 0

struct date{
	
	int jour;
	char mois[20];
	int annee;

};

struct date lire_date();

void afficher_date(struct date);

int  compare_date(struct date date1, struct date date2);

int est_ferier(struct date feriers[20], struct date my_date);

int main(){

	
	struct date my_date;
	
	struct date jours_feriers[20]={{1, "Janvier", 2024}, {1, "Avril", 2024}, {1, "Mai", 2024}, {8, "Mai", 2024}, {9, "Mai", 2024}, {20, "Mai", 2024},
	{14, "Juillet", 2024}, {15, "Aout", 2024}, {1, "Novembre", 2024}, {11, "Novembre", 2024}, {25, "Decembre", 2024}};
	
	my_date = lire_date();
	
	
	if (est_ferier(jours_feriers, my_date) == VRAI){
		printf("Le %d %s %d est ferie \n", my_date.jour, my_date.mois, my_date.annee);
	}else{
		printf("Le %d %s %d n'est pas ferie \n", my_date.jour, my_date.mois, my_date.annee);
	}

	return EXIT_SUCCESS;

}


struct date lire_date(){

	struct date date_entree;

	while (1) {
		printf("Veuillez entrer votre date au format : Jour(1-31), Mois(Janvier-Decembre), Annee(xxxx): \n ");
		scanf("%d %s %d", &date_entree.jour, date_entree.mois, &date_entree.annee);

		if (date_entree.jour < 1 || date_entree.jour > 31) {
		    printf("Veuillez entrer un jour valide \n");
		    continue;
		}

		char liste_des_mois[1000] = "Janvier Février Mars Avril Mai Juin Juillet Aout Semptembre Octobre Novembre Decembre";

		if (strstr(liste_des_mois, date_entree.mois) == NULL) {
		    printf("Veuillez entrer un mois valide \n");
		    continue;
		}

		if (date_entree.annee / 10000 != 0) {
		    printf("Veuillez entrer une année valide \n");
		    continue;
		}

		break;
	}

	return date_entree;
	
}

void afficher_date(struct date my_date){
	
	printf("La date saisie est : %d %s %d \n", my_date.jour, my_date.mois, my_date.annee);

}


int  compare_date(struct date date1, struct date date2){
	if (date1.jour == date2.jour && strcmp(date1.mois, date2.mois) == 0 && date1.annee == date2.annee){
		return VRAI;
	}
	return FAUX;
}


int est_ferier(struct date feriers[20], struct date my_date){
	
	int i;
	
	for (i=0; i<20; i++){
		if (compare_date(feriers[i], my_date) == VRAI){
			return VRAI;
		}
	}	
	return FAUX;

}
