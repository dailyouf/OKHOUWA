#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define N 50

struct pp_s{
	int pp1;
	int pp2;
};

void initialiser_tab_alea(int t[N], unsigned n);

void afficher_tab(int t[N], unsigned n);

struct pp_s min_min2_it(int t[N], int g, int d);

struct pp_s min_min2(int t[N], int g, int d);
	
int main(int argc, char * argv[]){

	unsigned n;
	long tmp_n;
	char *ptr;
	
	int tab[N];
	
	struct pp_s res;
	
	srand(time(NULL));

	if (argc != 2){
		printf("Il faut mettre un argumemt\n");
		return EXIT_FAILURE;
	}

	tmp_n = strtol(argv[1], &ptr, 10);
	
	if (strlen(ptr) > 0){
		printf("La converstion s'est pas bien passée \n");
		return EXIT_FAILURE;
	}
	
	
	if (tmp_n < 0){
		printf("Argumemt 1 négtif\n");
		return EXIT_FAILURE;
	}
	
	if (tmp_n > N){
		printf("Argumemt supérieur à 50\n");
		return EXIT_FAILURE;
	}
	
	n = tmp_n;
	
	/* printf("%u \n", n);*/
	
	initialiser_tab_alea(tab, n);
	
	afficher_tab(tab, n);
	
	res = min_min2(tab, 0, n);
	
	printf("%d %d \n", res.pp1, res.pp2);
	
	return EXIT_SUCCESS;
	
}

void initialiser_tab_alea(int t[N], unsigned n){
	int i;
	
	for (i=0; i<n; i++){
		t[i] = rand() % 100;	
	}
}

void afficher_tab(int t[N], unsigned n){
	int i;
	
	for (i=0; i<n; i++){
		printf("%d ", t[i]);
	}
	
	printf("\n");

}

struct pp_s min_min2_it(int t[N], int g, int d){
	
	int i;
	
	struct pp_s pps={t[g], t[g]};
	
	for (i=g+1; i<d; i++){
		if (t[i] < pps.pp1){
			pps.pp1 = t[i];
			continue;
		}
		
		if (t[i] < pps.pp2){
			pps.pp2 = t[i];
		}
	}
	
	return pps;

}

struct pp_s min_min2(int t[N], int g, int d){

	
	if ((d - g) == 2){
		if (t[d] >= t[g]){
			return (struct pp_s) {t[g], t[d]};
		}
		
		return (struct pp_s) {t[d], t[g]};
	}
	
	if (((d - g) % 2) == 0){
		int milieu = (d - g) / 2;
		struct pp_s min_gauche = min_min2(t, g, milieu);
		struct pp_s min_droite = min_min2(t, milieu + 1, d);
		
		if (min_gauche.pp1 <= min_droite.pp1){
			
			if (min_gauche.pp2 <= min_droite.pp1){
				return (struct pp_s) {min_gauche.pp1, min_gauche.pp2};
			}
			
			return (struct pp_s) {min_gauche.pp1, min_droite.pp1};
			
		} 
		
		if (min_droite.pp2 <= min_gauche.pp1){
			return (struct pp_s) {min_droite.pp1, min_droite.pp2};
		}
			
		return (struct pp_s) {min_droite.pp1, min_gauche.pp1};
		
	} 
	
	int milieu = (d - g) / 2;
	struct pp_s min_gauche = min_min2(t, g, milieu - 1);
	struct pp_s min_droite = min_min2(t, milieu + 1, d);
	
	if (min_gauche.pp1 <= min_droite.pp1){
			
		if (min_gauche.pp2 <= min_droite.pp1){
			if (t[milieu] < min_gauche.pp1) return (struct pp_s) {t[milieu], min_gauche.pp1};
			
			else if (t[milieu] < droite.pp1) return (struct pp_s) {min_gauche.pp1, t[milieu] < droite.pp1)};
			
			return (struct pp_s) {min_gauche.pp1, min_gauche.pp2};
		}
			
		return (struct pp_s) {min_gauche.pp1, min_droite.pp1};
			
	} 
		
	if (min_droite.pp2 <= min_gauche.pp1){
		if (t[milieu] < min_droite.pp1) return (struct pp_s) {t[milieu], min_droite.pp1};
			
		else if (t[milieu] < gauche.pp1) return (struct pp_s) {min_droite.pp1, t[milieu]};
	
		return (struct pp_s) {min_droite.pp1, min_droite.pp2};
	}
	
	if (t[milieu] < droite.pp1) return (struct pp_s) {t[milieu], min_droite.pp1};
	
	else if (t[milieu] < min_gauche.pp1) return (struct pp_s) {min_droite.pp1, t[milieu]};	

			
	return (struct pp_s) {min_droite.pp1, min_gauche.pp1};

}

