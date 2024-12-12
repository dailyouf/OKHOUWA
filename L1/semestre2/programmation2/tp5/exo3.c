#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 20

struct matrice {
	unsigned nb_lignes;
	unsigned nb_colonnes;
	int coeff[20][20];
};

void transposer_mat(struct matrice *am_t, const struct matrice *am);

void init_mat(struct matrice *m, int n, int p);

void reduire_mat(struct matrice *am_t);

void affichage(struct matrice *am);

void somme_mat(struct matrice *m1, struct matrice *m2, struct matrice *somme);

void produit_mat(struct matrice *m1, struct matrice *m2, struct matrice *produit);

int main(int argc, char * argv[]){
	
	unsigned n, p;
	
	struct matrice m, m_rev, somme, produit;
	
	if (argc != 3){	
		printf("Nombre argument non valide \n");
		return EXIT_FAILURE;
	}

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	
	init_mat(&m, n, p);
	
	affichage(&m);
	
	transposer_mat(&m_rev, &m);
	
	affichage(&m_rev);
		
	somme_mat(&m, &m_rev, &somme);
	
	affichage(&somme);
	
	produit_mat(&m, &m_rev, &produit);
	
	affichage(&produit);
	
	reduire_mat(&m_rev);
	
	affichage(&m_rev);
	
	return EXIT_SUCCESS;
}


void transposer_mat(struct matrice *am_t, const struct matrice *am){
	
	int i, j;
	
	am_t->nb_lignes = am->nb_colonnes;
	am_t->nb_colonnes = am->nb_lignes;
	
	for (i=0; i<am_t->nb_lignes; i++){
		for (j=0; j<am_t->nb_colonnes; j++){
			*( *(am_t->coeff + i) + j) = *( *(am->coeff + j) + i);
		}	
	}	
	
}	

void reduire_mat(struct matrice *am){
	int i, j;
	
	--am->nb_lignes;	
	--am->nb_colonnes;	
	
	for (i=0; i < am->nb_lignes; i++){
		for (j=0; j < am->nb_colonnes; j++){
			*( *(am->coeff + i) + j) = *( *(am->coeff + i + 1) + j + 1);	
		}
	}	

}


void affichage(struct matrice *m){
	int i, j;
	
	for (i=0; i<m->nb_lignes; i++){
		for (j=0; j<m->nb_colonnes;j++){
			printf("%3d ", *( *(m->coeff + i) + j));
		}
		printf("\n");
	}
	printf("\n");
	
}

void somme_mat(struct matrice *m1, struct matrice *m2, struct matrice *res) {
	
	int i, j;

	if (( m1->nb_lignes != m2->nb_lignes) || ( m1->nb_colonnes != m2->nb_colonnes)) {
		printf("Matrices ayant pas les memes dimentions");
		return;
	}
	
	res->nb_lignes = m1->nb_lignes;
	res->nb_colonnes = m1->nb_colonnes;
	
	for (i=0; i<res->nb_lignes; i++) {
		for (j=0; j<res->nb_colonnes; j++){
			
			*( *(res->coeff + i) + j) = *( *(m1->coeff + i) + j) + *( *(m2->coeff + i) + j);
			
		}
	}
	
}


void produit_mat(struct matrice *m1, struct matrice *m2, struct matrice *res) {
	
	int i, j, k;

	if ( m1->nb_lignes != m2->nb_colonnes) {
		printf("Matrices ayant pas les memes dimentions");
		return;
	}
	
	res->nb_lignes = m1->nb_lignes;
	res->nb_colonnes = m2->nb_colonnes;
	
	for (i=0; i<res->nb_lignes; i++) {
		for (j=0; j<res->nb_colonnes; j++){
			*( *(res->coeff + i) + j) = 0;
			for (k = 0; k < m1->nb_colonnes; k++){
				*( *(res->coeff + i) + j) += *( *(m1->coeff + i) + k) * *( *(m2->coeff + k) + j);
			}			
		}
	}
	
}

void init_mat(struct matrice *m, int n, int p){

	int i, j;
	
	srand(time(NULL));
		
	m->nb_lignes = n;
	m->nb_colonnes = p;
	
	for (i=0; i<n; i++){
		for (j=0; j<p;j++){
			*( *(m->coeff + i) + j) = rand() % 100;
		}
	}


}


