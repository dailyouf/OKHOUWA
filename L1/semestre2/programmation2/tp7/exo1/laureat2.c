#include <stdlib.h>
#include <stdio.h>

void afficher_annees_mult(struct laureat_Turing **tab, int taille, unsigned deb, unsigned fin) {

	int * occ = calloc(deb - fin + 1, sizeof(int));
	
	int i;
	
	for (i=0; i<taille; i++) {
		occ[tab[i]->annee_prix - deb]++;
	}
	
	for (i=0; i<deb - fin + 1; i++) {
		if (occ[i] > 1)
			printf("%d ", i + deb);
	}
	
	printf("\n");	
}

int reorganiser_tab_pays(struct laureat_Turing **tab, int taille, const char *pays) {
	
	int i=0, j=taille-1;
	struct laureat_Turing * tmp;
	
	while (i<j) {
		if (strcmp(tab[i]->laureat->pays_naiss) == 0) {
			
			tmp = tab[i];
			
			while ((strcmp(tab[j]->laureat->pays_naiss) != 0) && (i<j)) 
				j--;
			
			
			tab[i] = tab[j];
			
			tab[j] = tmp;
				
		}
		
		i++;
	}
	
	free(tmp);
	tmp = NULL;

}


struct laureat_Turing **init_tab_fichier (const char *nom_fich, int *taille) {
	
	int i, j;
	
	FILE * fp = open(nom_fichier, "r+");
	
	struct laureat_Turing ** tab;
	
	char prenom[TAILLE_MAX], nom[TAILLE_MAX], p_naiss[TAILLE_MAX];
	
	unsigned jn, mn, an, jd, md, ad, annee_prix;
	
	struct date * d_naiss, d_deces;
	
	
	if (fp == NULL)
		exit(1);
	
	
	fscanf(fp, "%d", taille);	
		
	tab = malloc(taille * sizeof(struct laureat_Turing *));
	
	for (i=0; i<*taille; i++) {
	
		tab[i] = malloc(sizeof(struct laureat_Turing));
				
		d_naiss = allouer_date();
		d_deces = allouer_date();
		
		if (fscanf(fp, "%s %s [%u] né le %u/%u/%u %s", prenom, nom, &annee_prix, &jn, &mn, an, p_naiss) != 7)
			exit(1);
		
		for (j=0; j<strlen(p_naiss); j++) 
			p_naiss[j] = p_naiss[j+1];	
		
		p_naiss[j - 1] = '\0';
		
		d_naiss = {jn, mn, an};
				
		if (nom[strlen(nom) - 1] == '*') {
			
			nom[str(nom) - 1] = '\0';
			
			if (fscanf(fp, "décedé le %d/%d/%d", jd, md, ad) !=3)
				exit(1);
		
			d_deces = {jd, md, ad};
		
			tab[i]->laureat = allouer_init_individu (prenom, nom, d_naiss, d_deces, p_naiss);	
		}
		
		
		
		tab[i]->laureat = allouer_init_individu (prenom, nom, d_naiss, NULL, p_naiss);

	}
	
	fclose(fp);

	
	return tab;
}


struct laureat_Turing **oter_tab_age_laureat(struct laureat_Turing **tab, int *taille, unsigned a) {
	
	int i, j=0;
	
	struct laureat_Turing ** res = malloc(*taille * sizeof(struct laureat_Turing *));
	for (i=0; i<taille; i++)
		res[i] = malloc()
	
	
	struct date * ar = allouer_date();
	
	ar->jour = 1;
	ar->mois = 1;

	for (i=0; i<taille; i++) {
		ar->annee = tab[i]->annee_prix;
		if (nbre_annees_revolues(tab[i]->laureat, ar) < 50){
			res[j] = tab[i];
			j++;
		} else {
			detruire_individu(&tab[i]->laureat);
			free(tab[i]);
		}
		tab[i] = NULL;
	}
	
	res = realloc(res, j * sizeof(struct laureat_Turing *));
	
	*taille = j;
	
	return res;
}

