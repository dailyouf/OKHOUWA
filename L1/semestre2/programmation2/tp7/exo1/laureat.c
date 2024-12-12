#include "laureat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct laureat_Turing ** init_tab_fichier(const char *nom_fich, int *taille){
	
	int j, i=0;
	
	FILE * fp;

	
	char nom[TAILLE_MAX_CHAINE];
	char prenom[TAILLE_MAX_CHAINE];
	int annee_prix;
	
	struct date * date_naiss;
	struct date * date_dec;
	
	char pays[TAILLE_MAX_CHAINE];
	
	
	if ((fp = fopen(nom_fich, "r")) == NULL){
		fprintf(stderr, "Erreur à l'ouverture du fichier text");
		exit(1);
	}
	
	fscanf(fp, "%d", taille);
	
	struct laureat_Turing ** tab = malloc(*taille * sizeof(struct laureat_Turing*));
	
	for (i=0; i<*taille; i++) 
		tab[i] = malloc(sizeof(struct laureat_Turing));
	
	
	i=0;
	
	while (i < *taille){
		
		date_naiss = allouer_date();
	
		if (fscanf(fp, "%s %s", nom, prenom) != 2){
			fprintf(stderr, "Erreur lors de la lecture du nom et prenom \n");
			exit(1);
		}
		
		if (fscanf(fp, " [%d]", &annee_prix) != 1){
			fprintf(stderr, "Erreur lors de la lecture de l'année d'obtention du loreat \n");
			exit(1);
		}
		
		if (fscanf(fp, " né(e) le %d/%d/%d", &date_naiss->jour, &date_naiss->mois, &date_naiss->annee) != 3) {
			fprintf(stderr, "Erreur lors de la lecture de la date de naissance \n");
			exit(1);
		}
		
		if (fscanf(fp, " %s", pays) != 1){
			fprintf(stderr, "Erreur lors de la lecture du pays \n");
			exit(1);
		}
		
		
		for (j=0; j<strlen(pays)-1; j++)
			pays[j] = pays[j+1];
		
		pays[j-1] = '\0';
		
		
		if (prenom[strlen(prenom) - 1] == '*'){
			
			date_dec = allouer_date();
			
			
			if (fscanf(fp, " décédé(e) le %d/%d/%d", &date_dec->jour, &date_dec->mois, &date_dec->annee) != 3) {
				fprintf(stderr, "Erreur lors de la lecture de la date de décès \n");
				exit(1);
			}
			
			prenom[strlen(prenom) - 1] = '\0';
						
			tab[i]->laureat = allouer_init_individu(prenom, nom, date_naiss, date_dec, pays);
			
		}
		
		else {
			tab[i]->laureat = allouer_init_individu(prenom, nom, date_naiss, NULL, pays);
		}
		
		tab[i]->annee_prix = annee_prix;
				
		i++;
		
	}
	
	detruire_date(&date_naiss);
	detruire_date(&date_dec);
	
	fclose(fp);
	
	return tab;

}


void afficher_annees_mult(struct laureat_Turing **tab, int taille, unsigned deb, unsigned fin) {
	
	int i, m=fin-deb+1;
	
	int * occ = calloc(m, sizeof(int));
	
	for (i=0; i<taille; i++) {
		if ((tab[i]->annee_prix > deb-1) && (tab[i]->annee_prix < fin+1)) {
			occ[tab[i]->annee_prix - deb]++;
		}
	}
	
	printf("Années multiples entre %d et %d sont : ", deb, fin);
	for (i=0; i<m; i++) {
		if (occ[i] > 1)
			printf("%d ", i+deb);
	}
	
	printf("\n");

}


int reorganiser_tab_pays(struct laureat_Turing **tab, int taille, const char *pays) {
	
	int i=0, j=taille-1;
	
	struct laureat_Turing * tmp;
	
	while (i<j) {
	
		if (strcmp(tab[i]->laureat->pays_naiss, pays) == 0){
			if (strcmp(tab[j]->laureat->pays_naiss, pays) != 0){
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
				/* ****** La ligne qui pose problème ******* */
				tmp=NULL;	
				/* ********** */
				continue;	
			}
			
			j--;
			continue;
		}
		
		i++;
	}
	
	free(tmp);
	
	return i-1;

}

struct laureat_Turing **oter_tab_age_laureat(struct laureat_Turing **tab, int *taille, unsigned a) {
	int i, j=0;

	struct date * date_prix = allouer_date();
	
	date_prix->jour = 1;
	date_prix->mois = 1;
	
	struct laureat_Turing ** new_tab = malloc(*taille * sizeof(struct laureat_Turing*));
	for (i=0; i<*taille; i++) 
		new_tab[i] = malloc(sizeof(struct laureat_Turing));	
	
	
	for (i=0; i<*taille; i++) {
		
		date_prix->annee = tab[i]->annee_prix;

		if (nbre_annees_revolues(tab[i]->laureat, date_prix) < a) {
			new_tab[j] = tab[i];
			j++;
			
		}
		
		else {
			detruire_individu(&tab[i]->laureat);
			free(tab[i]);
		}
		
		tab[i] = NULL;
			
	}
	
	
	*taille = j;


	res = realloc(res, j * sizeof(struct laureat_Turing *));
	
	detruire_date(&date_prix);
	
	return new_tab;

}


void trier_tab_age_laureat(struct laureat_Turing **tab, int taille) {

	int i, j;
	
	struct laureat_Turing * tmp;
	
	struct date * date_i = allouer_date();
	date_i->jour = 1;
	date_i->mois = 1;
	
	struct date * date_j = allouer_date();
	date_j->jour = 1;
	date_j->mois = 1;
	
	for (i=0; i<taille-1; i++) {
		
		for (j=i+1; j<taille; j++) {
		
			date_i->annee = tab[i]->annee_prix;
			date_j->annee = tab[j]->annee_prix;
			
			if (nbre_annees_revolues(tab[i]->laureat, date_i) - nbre_annees_revolues(tab[j]->laureat, date_j) > 0){
				
					tmp = tab[i];
					tab[i] = tab[j];
					tab[j] = tmp;
					
					tmp = NULL;
			}
		
		}
	
	}
	
	detruire_date(&date_i);
	detruire_date(&date_j);	
	
}


void sauv_tab_fichier(const char *nom_fich, struct laureat_Turing **tab, int * taille) {
	
	int i;
		
	FILE * fp = fopen(nom_fich, "w");
	
	fprintf(fp, "%d\n", *taille);
	
	for(i=0; i<*taille; i++) {
		
		if (tab[i]->laureat->date_deces == NULL) {
			fprintf(fp, "%s %s [%d] ", tab[i]->laureat->prenom, tab[i]->laureat->nom, tab[i]->annee_prix);
			fprintf(fp, "né(e) le %d/%d/%d ", tab[i]->laureat->date_naiss->jour, tab[i]->laureat->date_naiss->mois, tab[i]->laureat->date_naiss->annee);
			fprintf(fp, "(%s)", tab[i]->laureat->pays_naiss);
		}
		else {
			fprintf(fp, "%s %s* [%d] ", tab[i]->laureat->prenom, tab[i]->laureat->nom, tab[i]->annee_prix);
			fprintf(fp, "né(e) le %d/%d/%d ", tab[i]->laureat->date_naiss->jour, tab[i]->laureat->date_naiss->mois, tab[i]->laureat->date_naiss->annee);
			fprintf(fp, "(%s)", tab[i]->laureat->pays_naiss);
			fprintf(fp, " décédé(e) le %d/%d/%d ", tab[i]->laureat->date_deces->jour, tab[i]->laureat->date_deces->mois, tab[i]->laureat->date_deces->annee);
		}
		fprintf(fp, "\n");
		
	} 
	
	for (i=0; i<*taille; i++){
		detruire_individu(&tab[i]->laureat);
		free(tab[i]);
		tab[i]=NULL;
	}
	
	free(tab);
	tab = NULL;	
	
	*taille = 0;
	taille = NULL;
	
	fclose(fp);
	
}



