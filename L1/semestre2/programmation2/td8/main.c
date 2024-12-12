#include <stdlib.h>
#include <stdio.h>


struct mat_float * additionner_matrice(const struct mat_float * m1, const struct mat_float * m2); 

struct mat_float * produit_matrice(const struct mat_float * m1, const struct mat_float * m2); 

double det_matrice(const struct mat_float * m); 

int main(){



	return EXIT_SUCCESS;
}

struct mat_float * additionner_matrice(const struct mat_float * m1, const struct mat_float * m2) {
	
		int i, j;
		
		struct mat_float * res_mat = malloc(sizeof(struct mat_float));
		
		if ((m1->lig != m2->lig) || (m1->col != m2->col)) {
			fprintf(strerr, "Les matrices n'ont pas la même taille! \n");
			return NULL;		
		}
		
		
		res_mat->lig = m1->lig;
		res_mat->col = m1->col;
		
		res_mat->tab = malloc(res_mat->lig * sizeof(double *));
		
		for (i=0; i<res_mat->lig; i++) {
			res->tab[i] = malloc(res_mat->col * sizeof(double));
			for (j=0; j<res_mat->col; j++) {
				res->tab[i][j] = m1->tab[i][j] + m2->tab[i][j];
			}
		}
		
		return res_mat;
		
}

struct mat_float * produit_matrice(struct mat_float * m1, struct mat_float * m2) {
	
		int i, j, k;
		
		struct mat_float * res_mat = malloc(sizeof(struct mat_float));
		
		if (m1->col != m2->lig) {
			fprintf(strerr, "Les matrices n'ont pas les dimentsions appropriées! \n");
			return NULL;		
		}
		
		
		res_mat->lig = m1->lig;
		res_mat->col = m2->col;
		
		res_mat->tab = malloc(res_mat->lig * sizeof(double *));


		for (i=0; i<res_mat->lig; i++) {
			res->tab[i] = malloc(res_mat->col * sizeof(double));
			for (j=0; j<res_mat->col; j++) {
				res->tab[i][j]=0;
				for (k=0; k<m1->col; k++) {
					res->tab[i][j] += m1->tab[i][k] * m2->tab[k][j];
				}
			}
		}
		
		return res_mat;

}


double det_matrice(const struct mat_float * m) {
	
	int i;
	double res;
	
	if (m->lig =! m->col) {
		fprintf(strerr, "La matrice n'est pas carrée \n");
		return 0;
	}
	
	if (m->lig == 1) {
		return m->tab[0][0];
	}
	
	if (m->lig == 0) {
		return 1;
	}
	
	
	for (i=0; i<m->lig; i++) {
		
		
				
	}




	return res;

}
