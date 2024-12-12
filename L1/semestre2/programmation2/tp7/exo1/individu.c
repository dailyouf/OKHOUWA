#include "date.h" /* Cette inclusion n'est pas nécessaire */
#include "individu.h"
#include <string.h> /* pour strcpy */
#include <stdlib.h> /* pour malloc, free, sizeof */
#include <stdio.h> /* pour printf */

/** Fonction qui alloue l'espace mémoire sur tas pour un individu */
/* qu'elle initialise champ par champ avec les paramètres d'entrée */
/** et renvoie l'adresse du bloc alloué pour l'individu */
struct individu *allouer_init_individu (const char *prenom, const char *nom, const struct date *d_naiss, const struct date *d_deces, const char *p_naiss) {
	/* Allocation de l'individu */
	struct individu * ind = malloc(sizeof(struct individu));
	if (ind == NULL) {
		perror("Échec allocation individu");
		exit(EXIT_FAILURE);
	}
	/* Allocation et initialisation du prénom */
	ind->prenom = malloc(sizeof(char)*(strlen(prenom)+1));
	if (ind->prenom == NULL) {
		perror("Échec allocation prénom");
		exit(EXIT_FAILURE);
	}
	strcpy(ind->prenom, prenom);
	/* Allocation et initialisation du nom */
	ind->nom = malloc(sizeof(char)*(strlen(nom)+1));
	if (ind->nom == NULL) {
		perror("Échec allocation nom");
		exit(EXIT_FAILURE);
	}
	strcpy(ind->nom, nom);
	/* Allocation et initialisation du pays d'origine */
	ind->pays_naiss = malloc(sizeof(char)*(strlen(p_naiss)+1));
	if (ind->pays_naiss == NULL) {
		perror("Échec allocation pays d'origine");
		exit(EXIT_FAILURE);
	}
	strcpy(ind->pays_naiss, p_naiss);
	/* Allocation et initialisation de la date de naissance */
	ind->date_naiss = allouer_date();
	*(ind->date_naiss) = *d_naiss;
	/* Si nécessaire, allocation et initialisation de la date de décès */
	ind->date_deces = NULL;
	if (d_deces != NULL) {
		ind->date_deces = allouer_date();
		*(ind->date_deces) = *d_deces;
	}
	return ind;
}

/** Fonction qui libère toute la mémoire occupée par l'individu pointé par ind */
void detruire_individu (struct individu ** ind) {
	free((*ind)->nom);
	free((*ind)->prenom);
	detruire_date(&(*ind)->date_naiss);
	detruire_date(&(*ind)->date_deces);
	free((*ind)->pays_naiss);
	free(*ind);
	*ind = NULL;
}

/** Fonction qui affiche le prénom, le nom, la date et le pays de naissance */
/* (la date de décès si elle est connue) de l'individu pointé par ind */
void afficher_individu (const struct individu *ind) {
	printf("%s %s né(e) le ", ind->prenom, ind->nom);
	afficher_date(ind->date_naiss);
	printf(" (%s)", ind->pays_naiss);
	if (ind->date_deces != NULL) {	printf(" décédé(e) le "); afficher_date(ind->date_deces); }
}

/** Fonction qui calcule le nombre d'années révolues */
/* de l'individu pointé par ind à la date pointée par d */
/** Par exemple, un individu né le 7 avril 1950 */
/* a 49 années révolues le 7 avril 2000 et en a 50 le 8 avril 2000 */
/** Complexité : \Theta(1) */
int nbre_annees_revolues (const struct individu *ind, const struct date *d) {
	struct date d_copie = *(ind->date_naiss);
	int res = d->annee - d_copie.annee - 1;
	d_copie.annee = d->annee;
	if (comparer_date(&d_copie, d) < 0)
		++res;
	return res;
}
