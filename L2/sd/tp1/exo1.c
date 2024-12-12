#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define V_MAX 1000

struct compteur {
	int nb_cmp;
	int nb_afect;	
};


void affiche_tab(int taille, float * tab, int num);

float * recopie_tab(int taille, float * tab);

struct compteur * tri_selection(int taille, float * tab);

struct compteur * tri_insertion(int taille, float * tab);

struct compteur * tri_fusion(float * tab, int g, int d);

struct compteur * fusionner_tri_fusion(float * tab, int g, int m, int d);

struct compteur * tri_rapide(float * tab, int g, int d);

int partitionner_tri_rapide(float * tab, int g, int d, struct compteur * cpt);

struct compteur * tri_rapide(float * tab, int g, int d);

struct compteur * tri_shell(float * tab, int g, int d);

// Tri récursif par sélection
struct compteur * tri_selection_rec(int taille, float * tab, int i);
// Tri récursif par insertion
struct compteur * tri_insertion_rec(int taille, float * tab, int i);
// Tri récursif à la bulle
struct compteur * tri_bulle_rec(int taille, float * tab, int n);
// Tri non récursif par fusion
struct compteur * tri_fusion_nonrec(float * tab, int taille);
// Tri non récursif rapide
struct compteur * tri_rapide_nonrec(float * tab, int taille);


void liberer_tab(float ** tab);


int main(int argc, char ** argv) {
	
	srand(time(NULL));	
	
	int taille;
	
	int i;		

	float * tab1, * tab2, * tab3, * tab4, * tab5; 
	
	struct compteur * cpt1, *cpt2, *cpt3, *cpt4, *cpt5;


	printf("Veuillez entrer la taille du tableau suivi des élements eventuels du tableau \n");

	if (argc == 1) {
		printf("Pas assez d'arguments \n");
		exit(1);	
	}
	
	taille = atoi(argv[1]);
	
	tab1 = malloc(taille * sizeof(float));
	
	if (argc == 2) {
		for (i=0; i<taille; i++) {
			tab1[i] = ( rand() % V_MAX );
		}
		
	}
	
	else {
		
		if (taille != argc - 2) {
			printf("Erreur taille du tableau \n");
			exit(1);	
		}
		
		for (i=0; i<taille; i++) {
			tab1[i] = atof(argv[i + 2]);
		}	
	}
	
	
	printf("Tableau initial: ");
	affiche_tab(taille, tab1, 1);
	
	tab2 = recopie_tab(taille, tab1);
	tab3 = recopie_tab(taille, tab1);
	tab4 = recopie_tab(taille, tab1);
	tab5 = recopie_tab(taille, tab1);
	
	cpt1 = tri_selection(taille, tab1);
	affiche_tab(taille, tab1, 1);
	printf("Le tri par selection a réalisé: %d comparaison et %d affections \n", cpt1->nb_cmp, cpt1->nb_afect);
	 
	cpt2 = tri_insertion(taille, tab2);
	affiche_tab(taille, tab2, 2);
	printf("Le tri par insertion a réalisé: %d comparaison et %d affections \n", cpt2->nb_cmp, cpt2->nb_afect);
	
	cpt3 = tri_fusion(tab3, 0, taille-1);
	affiche_tab(taille, tab3, 3);
	printf("Le tri par fusion a réalisé: %d comparaison et %d affections \n", cpt3->nb_cmp, cpt3->nb_afect);
	
	cpt4 = tri_rapide(tab4, 0, taille-1);
	affiche_tab(taille, tab4, 4);
	printf("Le tri rapide a réalisé: %d comparaison et %d affections \n", cpt4->nb_cmp, cpt4->nb_afect);

	cpt5 = tri_shell(tab5, 0, taille-1);
	affiche_tab(taille, tab5, 5);
	printf("Le tri shell a réalisé: %d comparaison et %d affections \n", cpt5->nb_cmp, cpt5->nb_afect);	


	liberer_tab(&tab1);
	liberer_tab(&tab2);
	liberer_tab(&tab3);	
	liberer_tab(&tab4);	
	liberer_tab(&tab5);	

}

/* Ne compter que les comparaison de valeur et affectation de valeur
	on ne compte pas les comparaison d'indice et affectation d'indice*/


void affiche_tab(int taille, float * tab, int num) {
	
	int i;
	
	printf("tab%d : { ", num);
	
	if (taille > 20) {
		printf("Taille du tableau trop grande pour être affiché \n");
		return;
	}
	
	for (i=0; i<taille - 1; i++)
		printf("%.3g, ", tab[i]);
	
	printf("%lg }", tab[i]);
	
	printf("\n");
}


float * recopie_tab(int taille, float * tab) {
	
	int i;
	
	float * new_tab = malloc(taille * sizeof(float)); 
	
	for (i=0; i<taille; i++) {
		
		new_tab[i] = tab[i];
		
	}
	
	return new_tab;
}



struct compteur * tri_selection(int taille, float * tab) {
	
	int i, j, post_min;
	float tmp;
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->nb_cmp = 0;
	cpt->nb_afect = 0;
	
	for(i=0; i<taille-1; i++) {
		
		post_min = i;
		
		for (j=i+1; j<taille; j++) {
			cpt->nb_cmp++;
			if (tab[j] < tab[post_min]){
				post_min = j;
			}
		}
		
		tmp = tab[i];
		tab[i] = tab[post_min];
		tab[post_min] = tmp;
		
		cpt->nb_afect += 3;
	}
	
	return cpt;
}


struct compteur * tri_insertion(int taille, float * tab) {

	int i, j, min=0;
	float tmp;
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->nb_cmp = 0;
	cpt->nb_afect = 0;
	
	for (i=1; i<taille; i++) {
		cpt->nb_cmp++;
		if (tab[i] < tab[min])
			min = i;
	}
	
	tmp = tab[0];
	tab[0] = tab[min];
	tab[min] = tmp;
	
	cpt->nb_afect += 3;
	
	for (i=2; i<taille; i++) {
		
		j = i;
		tmp = tab[j];
		cpt->nb_afect++;
		 
		while (tmp < tab[j-1]) {
			cpt->nb_cmp++;
			tab[j] = tab[j-1];	
			cpt->nb_afect++;
			j--;
		}
		
		cpt->nb_cmp++;
		
		tab[j] = tmp;
		cpt->nb_afect++;
	
	}

	return cpt;
}

struct compteur * fusionner_tri_fusion(float * tab, int g, int m, int d) {
	
	int i, j, k;
	
	float * aux = malloc((d - g + 1) * sizeof(float));
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->nb_cmp = 0;
	cpt->nb_afect = 0;
	
	for (i = 0; i <= m - g; i++) {
        	cpt->nb_afect++;
        	aux[i] = tab[g + i];
    	}
    	
    	
    	for (j = m+1; j <= d; j++) {
        	cpt->nb_afect++;
        	aux[d + m + 1 - j - g] = tab[j];
    	}
	
	i = 0;
    	j = d-g;

	
    	for (k = g; k <= d; k++) {
             	cpt->nb_cmp++;
        	if (aux[i] <= aux[j]) {
			tab[k] = aux[i++];
            		cpt->nb_afect++;
        	} else {
            		tab[k] = aux[j--];
            		cpt->nb_afect++;
        	}
   	}
	
	return cpt;
}

struct compteur * tri_fusion(float * tab, int g, int d) {
	
	int m = g + (d - g) / 2;
	
	struct compteur *tmp1, *tmp2, *tmp3;
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->nb_cmp = 0;
	cpt->nb_afect = 0;
	

	if (d <= g) return cpt;	

	tmp1 = tri_fusion(tab, g, m);
	tmp2 = tri_fusion(tab, m+1, d);
	tmp3 = fusionner_tri_fusion(tab, g, m, d);	
	
	cpt->nb_cmp += tmp1->nb_cmp + tmp2->nb_cmp + tmp3->nb_cmp;
	cpt->nb_afect += tmp1->nb_afect + tmp2->nb_afect + tmp3->nb_afect;
	
	free(tmp1);
	free(tmp2);
	free(tmp3);

	
	return cpt;

}


int partitionner_tri_rapide(float * tab, int g, int d, struct compteur * cpt) {
	
	int i=g-1, j=d;
	float tmp, pivot=tab[d];
	
	cpt->nb_afect++;
	
	while ( 1+1 == 2 ) {
		
		while (tab[++i] < pivot) 
			cpt->nb_cmp++;

		cpt->nb_cmp++;
		
		while (tab[--j] > pivot) { 
			cpt->nb_cmp++;
			if (j == g) break;
		}

		cpt->nb_cmp++;
		
		if (i >= j) break;
		
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		
		cpt->nb_afect += 3;
		
	}
	
	tmp = tab[i];
	tab[i] = tab[d];
	tab[d] = tmp;
	
	cpt->nb_afect += 3;
			
	return i;


}


struct compteur * tri_rapide(float * tab, int g, int d) {
	
	int i;
	
	struct compteur *tmp1, *tmp2;
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->nb_cmp = 0;
	cpt->nb_afect = 0;

	
	if ( g >= d) return cpt;

	i = partitionner_tri_rapide(tab, g, d, cpt);
	
	tmp1 = tri_rapide(tab, g, i-1);
	tmp2 = tri_rapide(tab, i+1, d);
	
	cpt->nb_cmp += tmp1->nb_cmp + tmp2->nb_cmp;
	cpt->nb_afect += tmp1->nb_afect + tmp2->nb_afect;
	
	free(tmp1);
	free(tmp2);
		
	return cpt;
	
}

struct compteur * tri_shell(float * tab, int g, int d) {
    
	int i, j, h;
	
	float tmp;
    
	struct compteur * cpt = malloc(sizeof(struct compteur));
    	
	cpt->nb_cmp = 0;
	cpt->nb_afect = 0;
      
	for (h = 1; (3*h + 1) <= d-g; h = 3*h + 1);

	for (; h > 0; h /= 3) {
	
        	for (i = g + h; i <= d; i++) {
			
			cpt->nb_cmp++;
			
			for (j = i; j >= g + h && tab[j] < tab[j - h]; j -= h) {
			
                		tmp = tab[j - h];
				tab[j - h] = tab[j];
				tab[j] = tmp;
				
				cpt->nb_afect += 3;
				cpt->nb_cmp++;
                		
            		}
        	}
    	}
    
	return cpt;
}


void liberer_tab(float ** tab) {
	free(*tab);
	*tab = NULL;
}





/**   Partie en plus **/

/* Tri par sélection récursif */
struct compteur * tri_selection(int taille, float * tab) {
        
        struct compteur * cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;
        
        if (taille <= 1)
                return cpt;

        // Trouver le minimum
        int i, post_min = 0;
        for (i = 1; i < taille; i++) {
                cpt->nb_cmp++;
                if (tab[i] < tab[post_min]) {
                        post_min = i;
                }
        }
        
        // Échanger le premier élément avec le minimum
        float tmp = tab[0];
        tab[0] = tab[post_min];
        tab[post_min] = tmp;
        cpt->nb_afect += 3;
        
        // Appeler récursivement sur le sous-tableau
        struct compteur *cpt_rec = tri_selection(taille - 1, tab + 1);
        
        cpt->nb_cmp += cpt_rec->nb_cmp;
        cpt->nb_afect += cpt_rec->nb_afect;
        
        free(cpt_rec);
        return cpt;
}

/* Tri par insertion récursif */
struct compteur * tri_insertion(int taille, float * tab) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;

        if (taille <= 1)
                return cpt;

        struct compteur *cpt_rec = tri_insertion(taille - 1, tab);

        float dernier = tab[taille - 1];
        int i = taille - 2;
        
        while (i >= 0 && tab[i] > dernier) {
                tab[i + 1] = tab[i];
                i--;
                cpt->nb_afect++;
                cpt->nb_cmp++;
        }
        tab[i + 1] = dernier;
        cpt->nb_afect++;

        cpt->nb_cmp += cpt_rec->nb_cmp;
        cpt->nb_afect += cpt_rec->nb_afect;

        free(cpt_rec);
        return cpt;
}

/* Tri à bulles récursif */
struct compteur * tri_bulle(int taille, float * tab) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;

        if (taille <= 1)
                return cpt;

        for (int i = 0; i < taille - 1; i++) {
                cpt->nb_cmp++;
                if (tab[i] > tab[i + 1]) {
                        float tmp = tab[i];
                        tab[i] = tab[i + 1];
                        tab[i + 1] = tmp;
                        cpt->nb_afect += 3;
                }
        }

        struct compteur *cpt_rec = tri_bulle(taille - 1, tab);
        cpt->nb_cmp += cpt_rec->nb_cmp;
        cpt->nb_afect += cpt_rec->nb_afect;

        free(cpt_rec);
        return cpt;
}


/* Tri Shell récursif */
struct compteur * tri_shell_recursif(float *tab, int taille, int h) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;

        if (h == 0)
                return cpt;

        // Effectuer l'insertion par intervalle de h
        for (int i = h; i < taille; i++) {
                float tmp = tab[i];
                cpt->nb_afect++;
                int j;
                for (j = i; j >= h && tab[j - h] > tmp; j -= h) {
                        tab[j] = tab[j - h];
                        cpt->nb_afect++;
                        cpt->nb_cmp++;
                }
                tab[j] = tmp;
                cpt->nb_afect++;
        }

        // Appel récursif avec un h divisé par 3
        struct compteur *cpt_rec = tri_shell_recursif(tab, taille, h / 3);

        cpt->nb_cmp += cpt_rec->nb_cmp;
        cpt->nb_afect += cpt_rec->nb_afect;

        free(cpt_rec);
        return cpt;
}

/* Fonction initiale pour le tri Shell */
struct compteur * tri_shell(float *tab, int taille) {
        // Calcul du premier h selon la séquence de Knuth (3*h + 1)
        int h = 1;
        while (h < taille / 3) {
                h = 3 * h + 1;
        }

        // Appeler la fonction récursive de tri de Shell
        return tri_shell_recursif(tab, taille, h);
}


/* Fonction pour fusionner deux sous-tableaux */
struct compteur * fusionner(float *tab, int g, int m, int d) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;

        int n1 = m - g + 1;
        int n2 = d - m;

        float *gauche = malloc(n1 * sizeof(float));
        float *droite = malloc(n2 * sizeof(float));

        for (int i = 0; i < n1; i++) {
                gauche[i] = tab[g + i];
                cpt->nb_afect++;
        }
        for (int i = 0; i < n2; i++) {
                droite[i] = tab[m + 1 + i];
                cpt->nb_afect++;
        }

        int i = 0, j = 0, k = g;
        while (i < n1 && j < n2) {
                cpt->nb_cmp++;
                if (gauche[i] <= droite[j]) {
                        tab[k++] = gauche[i++];
                        cpt->nb_afect++;
                } else {
                        tab[k++] = droite[j++];
                        cpt->nb_afect++;
                }
        }

        while (i < n1) {
                tab[k++] = gauche[i++];
                cpt->nb_afect++;
        }

        while (j < n2) {
                tab[k++] = droite[j++];
                cpt->nb_afect++;
        }

        free(gauche);
        free(droite);

        return cpt;
}

/* Fonction de tri fusion non récursif */
struct compteur * tri_fusion(float *tab, int taille) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;

        for (int largeur = 1; largeur < taille; largeur *= 2) {
                for (int gauche = 0; gauche < taille - largeur; gauche += 2 * largeur) {
                        int milieu = gauche + largeur - 1;
                        int droite = (gauche + 2 * largeur - 1 < taille) ? (gauche + 2 * largeur - 1) : (taille - 1);

                        struct compteur *cpt_fusion = fusionner(tab, gauche, milieu, droite);
                        cpt->nb_cmp += cpt_fusion->nb_cmp;
                        cpt->nb_afect += cpt_fusion->nb_afect;
                        free(cpt_fusion);
                }
        }

        return cpt;
}

/* Fonction de partitionnement pour le tri rapide */
int partitionner(float *tab, int g, int d, struct compteur *cpt) {
        float pivot = tab[d];
        int i = g - 1;

        for (int j = g; j < d; j++) {
                cpt->nb_cmp++;
                if (tab[j] < pivot) {
                        i++;
                        float tmp = tab[i];
                        tab[i] = tab[j];
                        tab[j] = tmp;
                        cpt->nb_afect += 3;
                }
        }

        float tmp = tab[i + 1];
        tab[i + 1] = tab[d];
        tab[d] = tmp;
        cpt->nb_afect += 3;

        return i + 1;
}

/* Fonction de tri rapide non récursif */
struct compteur * tri_rapide(float *tab, int taille) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->nb_cmp = 0;
        cpt->nb_afect = 0;

        int *pile = malloc(taille * sizeof(int));
        int top = -1;

        pile[++top] = 0;
        pile[++top] = taille - 1;

        while (top >= 0) {
                int d = pile[top--];
                int g = pile[top--];

                if (g < d) {
                        int pivot = partitionner(tab, g, d, cpt);

                        if (pivot - 1 > g) {
                                pile[++top] = g;
                                pile[++top] = pivot - 1;
                        }

                        if (pivot + 1 < d) {
                                pile[++top] = pivot + 1;
                                pile[++top] = d;
                        }
                }
        }

        free(pile);
        return cpt;
}


