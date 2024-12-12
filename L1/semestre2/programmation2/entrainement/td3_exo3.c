#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define N 50

static unsigned C_bin=0, C_mem=0, C_ter=0;

unsigned binomial(unsigned n, unsigned p);

unsigned binomial_mem(unsigned n, unsigned p);
unsigned binomial_mem_aux(unsigned tab[N][N], unsigned n, unsigned p);

unsigned binomial_ter(unsigned n, unsigned p);
unsigned binomial_ter_aux(unsigned n, unsigned p, long double res);

unsigned binomial_iter(unsigned n, unsigned p);


int main(int argc, char ** argv){

	unsigned n, p;
	int tmp_n, tmp_p;
	char * ptr;
	
	time_t t_debut1, t_debut2, t_debut3, t_debut4;
	double duree_exec;
	
	unsigned res1, res2, res3, res4;	
	
	if (argc != 3){
		printf("Nombre d'arguments incorrect...");
		// usage_bin(argv[0]);
		return EXIT_FAILURE;
	}
	
	tmp_n = strtol(argv[1], &ptr, 10);
	if (strlen(ptr) > 0 || tmp_n < 0) {
		printf("Le premier argument n'est pas valide...");
		// usage_bin(argv[0]);
		return EXIT_FAILURE;
	}
	
	n = tmp_n;
	
	tmp_p = strtol(argv[2], &ptr, 10);
	if (strlen(ptr) > 0 || tmp_p < 0) {
		printf("Le deuxième argument n'est pas valide...");
		// usage_bin(argv[0]);
		return EXIT_FAILURE;
	}
	
	p = tmp_p;

	t_debut4 = clock();
	res4 = binomial_iter(n, p);
	duree_exec = (double) (clock() - t_debut4) / CLOCKS_PER_SEC;
	printf("Calcul avec la version itérative après %lg secondes: coef binom = %u \n", duree_exec, res4);
	
	t_debut3 = clock();
	res3 = binomial_ter(n, p);
	duree_exec = (double) (clock() - t_debut3) / CLOCKS_PER_SEC;
	printf("Calcul avec la version terminale après %u appels et %lg secondes: coef binom = %u \n", C_ter, duree_exec, res3);
	
	t_debut2 = clock();
	res2 = binomial_mem(n, p);
	duree_exec = (double) (clock() - t_debut2) / CLOCKS_PER_SEC;
	printf("Calcul avec la mémoisation après %u appels et %lg secondes: coef binom = %u \n", C_mem, duree_exec, res2);
	
	t_debut1 = clock();
	res1 = binomial(n, p);
	duree_exec = (double) (clock() - t_debut1) / CLOCKS_PER_SEC;
	printf("Calcul avec la version normale après %u appels et %lg secondes: coef binom = %u \n", C_bin, duree_exec,res1);
	
	
	return EXIT_SUCCESS;
}

unsigned binomial(unsigned n, unsigned p){
	
	++C_bin;
	
	if (p > n) return 0;
	if (p==0 || n==p) return 1;
	
	return binomial(--n, p) + binomial(--n, --p);
	
}

unsigned binomial_mem_aux(unsigned tab[N][N], unsigned n, unsigned p){
	
	++C_mem;	
	
	if (p > n) return 0;
	if (p==0 || n==p) return 1;
	
	if (tab[n][p] == 0){
		tab[n][p] = binomial_mem_aux(tab, --n, p) + binomial_mem_aux(tab, --n, --p);
	}
	
	return tab[n][p];

}

unsigned binomial_mem(unsigned n, unsigned p){
	unsigned tab[N][N] = {0};
	return binomial_mem_aux (tab, n, p);
}

unsigned binomial_ter_aux(unsigned n, unsigned p, long double res){
	
	if (0 == p) return (unsigned) res;
	++C_ter;
	
	return binomial_ter_aux(n--, p--, ((double) n / p) * res);
}

unsigned binomial_ter(unsigned n, unsigned p){
	++C_ter;
	
	if (p > n) return 0;
	if (p==0 || n==p) return 1;
	
	return binomial_ter_aux(n, p, 1);
}


unsigned binomial_iter(unsigned n, unsigned p){
	
	int i;
	long double res;

	if (p > n) return 0;
	if (p==0 || n==p) return 1;
	
	
	for(i=0; i< (n-p); i++){
		
		res *= (double) (n - i) / (n - p - i);
	
	}
	
	return (unsigned) res;
}


