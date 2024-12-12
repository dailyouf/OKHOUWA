#ifndef DATE_H /* garde d'inclusion */
#define DATE_H

struct date {
	unsigned jour;
	unsigned mois;
	unsigned annee;
};

/** Fonction qui alloue de l'espace sur le tas pour une struct date */
/* et renvoie l'adresse du bloc alloué */
struct date * allouer_date(void);

/** Fonction qui affiche les valeurs des champs de la date passée en argument */
void afficher_date(const struct date *);

/** Fonction qui renvoie -1 si d1 est antérieure à d2, */
/**          qui renvoie 1 si d1 est postérieure à d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date *d1, const struct date * d2);

/** Fonction qui libère tout l'espace occupé sur le tas par une date */
void detruire_date (struct date **);

/** Renvoie le nombre de jours du mois de février de l'année reçue en entrée */
unsigned nbre_jours_fev (unsigned);

/** Renvoie le nombre de jours du couple (année, mois) reçu en entrée */
unsigned nbre_jours_mois (unsigned, unsigned);

/** Calcule, en an(s), mois et jour(s), l'écart entre les dates pointées par d1 et d2 */
/** N.B. On suppose que la date pointée par d2 est postérieure à celle pointée par d1 */
/* et qu'il y a au moins une année complète entre les deux dates */
/* (c'est suffisant pour l'usage qu'on en fait pour le TP du 25 avril 2024) */
struct date ecart_dates (const struct date *, const struct date *);

#endif
