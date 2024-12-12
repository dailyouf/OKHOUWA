#include<stdlib.h>
#include<stdio.h>


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


int main(int argc, char ** argv){

	char * ptr;
	int dp, dq;
	struct polynome * p, q;
	
	if (argc != 2) {
		printf("Nomre de caractères insuffisant \n");
		exit(1);
	}
	
	dp = atoi(argv[1]);
	dq = atoi(argv[1]);
	
	if ((dp < -1) || (dq < -1)) {
		printf("degré trop petits \n");
		exit(1);
	}
	
	p = creer_polynome(dp);
	q = creer_polynome(dq);
	
	
	
	return EXIT_SUCCESS;
}

struct polynome * creer_polynome(int n){

	struct polynome * res = malloc(sizeof(struct polynome));
	
	if (res == NULL){
		printf("Echec");
		exit(1);
	}
	
	res->coefficients = calloc(n, sizeof(int));
	
	if (res->coefficients == NULL){
		printf("Echec");
		exit(1);
	}
	
	res->taille=0;
	
	res->degre=-1;
	
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
		
		p->taille = p- >degre + 1;
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

	int i, d_min, d_max;
	
	struct polynome * pg;
	
	struct polynome * res;
	
	
	if (p->degre > q->degre){
		d_max = p->degre;
		d_min = q->degre;
		pg=p;
	}else{
		d_max = q->degre;
		d_min = p->degre;
		pg=q;
	}
	
	res = creer_polynome(pg->taille);
	
	for (i=0; i<d_min; i++)
		res->coefficients[i] = p->coefficients[i] + q->coefficients[i];

	for (;i<pg->taille; i++) 
		res->coefficients[i] = pg[i];
		
	
	while(res->coefficients[degre] == 0) res->degre--;
	
	reformater_polynome(res);
	
	return res;
}

struct polynome * multiplier_polynome(struct polynome * p, struct polynome * q){

	int i, j;
	
	struct polynome * res = creer_polynome(p->degre + q->degre + 1);
	
	res->degre = p->degre + q->degre;
	
	/*
	for (int i = 0; i < res->degre + 1; i++) {
        	res->coefficients[i] += 0;
    	}
    	*/
    	
    	for (int i = 0; i <= p->degre; i++) {
        	for (int j = 0; j <= q->degre; j++) {
        	    res->coefficients[i + j] += p->coefficients[i] * q->coefficients[j];
        	}
    	}
    	
    	
    	while(res->coefficients[degre] == 0) res->degre--;
	
	reformater_polynome(res);
	
	
	return res;

}

struct polynome * deriver_polynome(struct polynome * p) {
	
	int i;
	struct polynome * res;
	
	creer_polynome(p->taille - 1);
	
	for (i=0; i<res->taille; i++){
		res->coefficients[i] = p->coefficients[i+1] * (i+1);
	}
		
	reformater_polynome(res);

	return res;
}


void afficher_poly(struct polynome * p) {

	int i;
	
	if (p->degre=-1) printf("0");
	
	for (i=0; i<p->degre + 1; i++) {
	
		if (i==0) printf(" + %d", p->coefficients[0]);
			
		else printf(" + %d*X^%d", p->coefficients[i], i);
			
	}
	
	print("\n");
}


void evaluer_poly(struct polynome * p) {
	
	int i;
	double a;
	double res=0;
	
	scanf("%lg \n", &a);
	
	for (i=p->degre; i>0; i--) {
		res += p->coefficients[i];
		res *= a; 
	}
	
	res += p->coefficients[0];
	
	printf("%lg \n", res);
}


