#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "polynome.h"



struct polynome * creer_polynome(int n){
	
	int i;
	srand(time(NULL));
	
	struct polynome * res = malloc(sizeof(struct polynome));
	
	if (res == NULL){
		printf("Echec");
		exit(1);
	}
	
	res->coefficients = malloc(n*sizeof(int));
	
	if (res->coefficients == NULL){
		printf("Echec");
		exit(1);
	}
	
	for (i=0; i<n; i++) {
		res->coefficients[i] = 	(rand() % 19) - 9;
	}
	
	res->taille=n;
	
	res->degre=n-1;
	
	return res;
	
}

void reformater_polynome(struct polynome * p){
	
	int i;
	
	if (p->taille != p->degre + 1){
		
		int * coeff = malloc((p->degre + 1) * sizeof(int));
		
		if (coeff == NULL){
			printf("Echec");
			exit(1);
		}
		
		for (i=0; i<(p->degre + 1); i++){
			coeff[i] = p->coefficients[i];
		}
		
		free(p->coefficients);
		
		p->coefficients = coeff;
		
		p->taille = p->degre + 1;
	}
}

void detruire_polynome(struct polynome ** p){
	if (*p != NULL) {
	
		if ((*p)->coefficients != NULL){
			free((*p)->coefficients);
			(*p)->coefficients= NULL;
		}
		
		free(*p);
		*p=NULL;
	}	
}

void scalaire_polynome(struct polynome * p, int a){
	int i;
	
	for (i=0; i<p->taille; i++){
		p->coefficients[i] *= a;
	}	
	
	reformater_polynome(p);
}


struct polynome * additionner_polynome(struct polynome * p, struct polynome * q){

	int i, d_min;
	
	struct polynome * pg;
	
	struct polynome * res;
	
	
	if (p->degre > q->degre){
		d_min = q->degre;
		pg=p;
	}else{
		d_min = p->degre;
		pg=q;
	}
	
	res = creer_polynome(pg->taille);
	
	for (i=0; i<d_min; i++)
		res->coefficients[i] = p->coefficients[i] + q->coefficients[i];

	for (;i<pg->taille; i++) 
		res->coefficients[i] = pg->coefficients[i];
		
	
	while(res->coefficients[res->degre] == 0) res->degre--;
	
	reformater_polynome(res);
	
	return res;
}

struct polynome * multiplier_polynome(struct polynome * p, struct polynome * q){

	int i, j;
	
	struct polynome * res = creer_polynome(p->degre + q->degre + 1);
	
	res->degre = p->degre + q->degre;
	
	for (i = 0; i < res->degre + 1; i++) {
        	res->coefficients[i] += 0;
    	}
    	
    	
    	for (i = 0; i <= p->degre; i++) {
        	for (j = 0; j <= q->degre; j++) {
        	    res->coefficients[i + j] += p->coefficients[i] * q->coefficients[j];
        	}
    	}
    	
    	
    	while(res->coefficients[res->degre] == 0) res->degre--;
	
	reformater_polynome(res);
	
	
	return res;

}

struct polynome * deriver_polynome(struct polynome * p) {
	
	int i;
	struct polynome * res = creer_polynome(p->taille - 1);
	
	for (i=0; i<res->taille; i++){
		res->coefficients[i] = p->coefficients[i+1] * (i+1);
	}
		
	reformater_polynome(res);

	return res;
}


void afficher_poly(struct polynome * p) {

	int i;
	
	if (p->degre==-1) printf("0 \n");
	
	for (i=p->degre; i>-1; i--) {
	
		if (i==0) printf("%d \n", p->coefficients[0]);
		
		else if (i==1) printf("%d*X + ", p->coefficients[i]);
		
		else printf("%d*X^%d + ", p->coefficients[i], i);		
	}
	
}


void evaluer_poly(struct polynome * p) {
	
	int i;
	double a;
	double res=0;
	
	scanf("%lg", &a);
	
	for (i=p->degre; i>0; i--) {
		res += p->coefficients[i];
		res *= a; 
	}
	
	res += p->coefficients[0];
	
	printf("%lg \n", res);
}

