#ifndef LAUREAT_H /* garde d'inclusion */
#define LAUREAT_H

#include "date.h"
#include "individu.h"

#define TAILLE_MAX_CHAINE 50


struct laureat_Turing {
	struct individu * laureat;
	unsigned annee_prix;
};

struct laureat_Turing ** init_tab_fichier(const char *nom_fich, int * taille);

void afficher_annees_mult(struct laureat_Turing **tab, int taille, unsigned deb, unsigned fin);

int reorganiser_tab_pays(struct laureat_Turing **tab, int taille, const char *pays);

struct laureat_Turing **oter_tab_age_laureat(struct laureat_Turing **tab, int *taille, unsigned a);

void trier_tab_age_laureat(struct laureat_Turing **tab, int taille);


void sauv_tab_fichier(const char *nom_fich, struct laureat_Turing **tab, int * taille);


#endif
