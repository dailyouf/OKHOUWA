#ifndef POLYNOME_H
#define POLYNOME_H

struct polynome {
	int * coefficients;
	int taille;
	int degre;
};

struct polynome * creer_polynome(int n);

void reformater_polynome(struct polynome * p);

void detruire_polynome(struct polynome ** p);

void scalaire_polynome(struct polynome * p, int a);

struct polynome * additionner_polynome(struct polynome * p, struct polynome * q);

struct polynome * multiplier_polynome(struct polynome * p, struct polynome * q);

struct polynome * deriver_polynome(struct polynome * p);

void afficher_poly(struct polynome * p);

void evaluer_poly(struct polynome * p);

#endif
