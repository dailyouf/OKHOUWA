#ifndef INDIVIDU_H /* garde d'inclusion */
#define INDIVIDU_H

#include "date.h"

struct individu {
		char * nom; /* nom de l'individu */
		char * prenom; /* prenom de l'individu */
		struct date * date_naiss; /* date de naissance de l'individu */
		struct date * date_deces; /* date de deces de l'individu, NULL si l'individu est vivant */
		char * pays_naiss; /* pays de naissance de l'individu */
};

/** Fonction qui alloue l'espace mémoire sur tas pour un individu */
/* qu'elle initialise champ par champ avec les paramètres d'entrée */
/** et renvoie l'adresse du bloc alloué pour l'individu */
struct individu * allouer_init_individu (const char *prenom, const char *nom, const struct date *d_naiss, const struct date *d_deces, const char *p_naiss);

/** Fonction qui libère toute la mémoire occupée sur le tas */
/* par l'individu dont l'adresse est pointée par ind */
void detruire_individu (struct individu **ind);

/** Fonction qui affiche le prénom, le nom, la date et le pays de naissance */
/* (la date de décès si elle est connue) de l'individu pointé par ind */
void afficher_individu (const struct individu *ind);

/** Fonction qui calcule le nombre d'années révolues */
/* de l'individu pointé par ind à la date pointée par d */
/** Par exemple, un individu né le 7 avril 1950 */
/* a 49 années révolues le 7 avril 2000 et en a 50 le 8 avril 2000 */
int nbre_annees_revolues (const struct individu * ind, const struct date * d);

#endif
