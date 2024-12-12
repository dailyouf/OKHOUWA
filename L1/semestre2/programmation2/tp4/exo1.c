#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define N 50

static unsigned C_bin=0, C_mem=0, C_ter=0;

unsigned binomial(unsigned n, unsigned p);

unsigned binomial_mem(unsigned n, unsigned p);
unsigned binomial_mem_aux(unsigned n, unsigned p, unsigned binomial_tab[N][N]);

unsigned binomial_ter(unsigned n, unsigned p);
unsigned binomial_ter_aux(unsigned n, unsigned p, long double res);

unsigned binomial_iter(unsigned n, unsigned p);

int main(int argc, char * argv[]){

	unsigned n, p;
	long tmp_n, tmp_p;
	char *ptr;
	unsigned res1, res2, res3, res4;
	
	time_t t_debut1, t_debut2, t_debut3, t_debut4;
	
	double duree_exec;
	
	if (argc != 3){
		printf("Il faut mettre 2 argumemts ... \n");
		// usage_bin(argv[0]);
		return EXIT_FAILURE;
	}

	/*Agumemt 1*/
	tmp_n = strtol(argv[1], &ptr, 10);
	
	if (strlen(ptr) > 0){
		printf("La converstion s'est pas bien passée \n");
		return EXIT_FAILURE;
	}
	
	
	if (tmp_n < 0){
		printf("Argumemt 1 négtif ... \n");
		return EXIT_FAILURE;
	}
	
	/*Agumemt 2*/
	tmp_p = strtol(argv[2], &ptr, 10);
	
	if (strlen(ptr) > 0){
		printf("La converstion s'est pas bien passée \n");
		return EXIT_FAILURE;
	}
	
	
	if (tmp_p < 0){
		printf("Argumemt 2 négtif ... \n");
		return EXIT_FAILURE;
	}
	
	
	n = tmp_n;
	p = tmp_p;
	
	// printf("%u %u \n", n, p);
	
	
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
	if ((0 == p) || (p == n)) return 1;
	
	return binomial(n - 1, p) + binomial(n - 1, p - 1);
	

}

unsigned binomial_mem_aux(unsigned n, unsigned p, unsigned binomial_tab[N][N]){
	++C_mem;
	if (p > n) return 0;
	if ((0 == p) || (p == n)) return 1;
	
	if (binomial_tab[n][p] == 0){
		binomial_tab[n][p] = binomial_mem_aux(n - 1, p, binomial_tab) + binomial_mem_aux(n - 1, p - 1, binomial_tab);
	}
	
	return binomial_tab[n][p];
}


unsigned binomial_mem(unsigned n, unsigned p){
	unsigned binomial_tab[N][N] = {0};
	return binomial_mem_aux (n, p, binomial_tab);
}


unsigned binomial_ter_aux(unsigned n, unsigned p, long double res){
	
	if (0 == p) return (unsigned) res ;
	
	++C_ter;
	
	return binomial_ter_aux	(n-1, p-1, ( (double) n / p) * res);
}


unsigned binomial_ter(unsigned n, unsigned p){
	
	++C_ter;
	
	if (p > n) return 0;
	if ((0 == p) || (p == n)) return 1;
	
	return binomial_ter_aux(n, p, 1);

}

unsigned binomial_iter(unsigned n, unsigned p){
	
	int i;
	long double res=1;
	
	if (p > n) return 0;
	if ((0 == p) || (p == n)) return 1;

	for(i=0; i < (n-p); i++){
		
		res *= (double) (n - i) / (n - p - i);
	
	}
	 
	return (unsigned) res;


}












