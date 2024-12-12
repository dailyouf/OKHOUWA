#include <stdlib.h>
#include <stdio.h>


struct polynome {
	int * coefficients;
	int taille;
	int degre;
};

struct polynome * creer_polynome(int n);

void detruire_polynome(struct polynome ** p);

void reformater_polynome(struct polynome * p);

void scalaire_polynome(struct polynome * p, int a);

struct polynome * additionner_polynome(struct polynome * p, struct polyome * q);

struct polynome * multiplier_polynome(struct polynome * p, struct polyome * q);

struct polynome * deriver_polynome(struct polynome * p);

int main() {


	return EXIT_SUCCESS;
}

struct polynome * creer_polynome(int n) {
	
	struct polynome * p = malloc(sizeof(struct polynome));
	
	p->coefficients = calloc(n, sizeof(int));
	
	p->taille = n;
	p->degre = n-1;
	
	
	return p;
}

void reformater_polynome(struct polynome * p) {
	
	int i;
	
	struct polynome * res;
	
	if (p->taille != p->degre + 1) {
		
		res = creer_polynome(p->degre + 1);
	
		res->degre = p->degre;
	
		res->taille = p->degre + 1;
		
		for (i=0; i<res->taille; i++)
			res->coefficients[i] = p->coefficients[i];
		
		detruire_polynome(&p);
		p = res;
	}
	
}


void detruire_polynome(struct polynome ** p) {
	
	if (*p =! NULL) {
		free((*p)->coefficients);
		(*p)->coefficients = NULL;
		
		free(*p);
		*p = NULL;
	}
 
}

void scalaire_polynome(struct polynome * p, int a) {
	
	for (int i=0; i<p->taille; i++)
		p->coefficients[i] *= a;

}


struct polynome * additionner_polynome(struct polynome * p, struct polyome * q) {
	
	int i;
	
	struct polynome * pg = (p->taille > q->taille) ?  p : q;
	
	int min_taille = (p->taille > q->taille) ? q->taille : p->taille;
	
	
	struct polynome * res = creer_polynome(pg->taille);
	
	
	for (i=0; i<min_taille; i++)
		res->coefficients[i] = p->coefficients[i] + q->coefficients[i];
	
	
	for(;i<pg->taille;i++)
		res->coefficients[i] = pg->coefficients[i];
		
	while (!(res->coefficients[res->degre])) res->degre--;
	
	reformater_polynome(res);	
		
	return res;
}

struct polynome * multiplier_polynome(struct polynome * p, struct polyome * q) {
	
	int i, j;
	
	struct polynome * res = creer_polynome(p->taille + q->taille);
	
	for (i=0; i<res->taille; i++){
		res->coefficients[i] = 0;
	}
	
	for (i=0; i<p->coefficients; i++){
		for (j=0; j<q->coefficients; j++)
			res->coefficients[i + j] += p->coefficients[i] * q->coefficients[j];
	}
	
	while (!(res->coefficients[res->degre])) res->degre--;
	
	reformater_polynome(res);	
		
	return res;
	

}


struct polynome * deriver_polynome(struct polynome * p) {
	
	int i;
	
	struct polynome * res = creer_polynome(p->degre);
	
	for (i=0; i<p->taille; p++)
		res->coefficients[i] = p->coefficients[i+1];
		
	return res;
}
