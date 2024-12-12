#include "date.h"
#include <stdio.h> /* pour printf, perror */
#include <stdlib.h> /* pour EXIT_FAILURE, exit, malloc, free */
#include <time.h> /* pour time_t, struct tm, time et localtime */

/** Fonction qui alloue de l'espace sur le tas pour une struct date */
/* et renvoie l'adresse du bloc alloué */
struct date * allouer_date(void) {
	struct date * res = malloc(sizeof(struct date));
	if (res == NULL) {
		perror("Échec allocation date");
		exit(EXIT_FAILURE);
	}
	return res;
}

/** Fonction qui affiche les valeurs des champs de la date passée en argument */
void afficher_date(const struct date * d) {
	printf("%u/%u/%u", d->jour, d->mois, d->annee);
}

/** Fonction qui renvoie -1 si d1 est antérieure à d2, */
/**          qui renvoie 1 si d1 est postérieure à d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date * d1, const struct date * d2) {
	if(d1->annee < d2->annee)
		return -1;
	if (d1->annee > d2->annee)
		return 1;
	if (d1->mois < d2->mois)
		return -1;
	if (d1->mois > d2->mois)
		return 1;
	if (d1->jour < d2->jour)
		return -1;
	if (d1->jour > d2->jour)
		return 1;
	return 0;
}

/** Fonction qui libère tout l'espace occupé sur le tas par une date */
void detruire_date (struct date ** d) {
	if (*d != NULL) free(*d);
	*d = NULL;
}

/** Renvoie le nombre de jours du mois de février de l'année reçue en entrée */
unsigned nbre_jours_fev (unsigned annee) {
  if (annee%400 == 0) return 29;
  if (annee%4 == 0 && annee%100 >0) return 29;
  return 28;
}

/** Renvoie le nombre de jours du couple (année, mois) reçu en entrée */
unsigned nbre_jours_mois (unsigned annee, unsigned mois) {
  if (mois == 4 || mois == 6 || mois == 9 || mois == 11)
    return 30;
  if (mois == 2)
    return nbre_jours_fev(annee);
  return 31;
}

/** Calcule, en an(s), mois et jour(s), l'écart entre les dates pointées par d1 et d2 */
/** N.B. On suppose que la date pointée par d2 est postérieure à celle pointée par d1 */
/* et qu'il y a au moins une année complète entre les deux dates */
/* (c'est suffisant pour l'usage qu'on en fait pour le TP du 25 avril 2024) */
struct date ecart_dates (const struct date *d1, const struct date *d2) {
	struct date res = {0, 0, 0};
	res.annee = d2->annee - d1->annee -1;
	if (d2->mois > d1->mois) { ++res.annee; res.mois = d2->mois - d1->mois; }
	else {	res.mois = 12 - d1->mois + d2->mois - 1; }
	if (d2->jour >= d1->mois) { ++res.mois; res.jour = d2->jour - d1->jour; }
	else {	res.jour = nbre_jours_mois(d1->annee, d1->mois) - d1->jour + d2->jour; }
	if (res.mois == 12) {	++res.annee; res.mois = 0; }
	return res;
}
