#include <stdlib.h>
#include <stdio.h>

#define N 10
#define TRUE 1
#define FALSE 0

void Affichage(double tab[N], int n);

void tri_bulles(double tab[N], int n);
int recherche_dichotomique(double tab[N], int n, double d);

void tri_selection(double tab[N], int n);
void tri_insertion(double tab[N], int n);
void tri_fusion(double tab[N], int debut, int fin);
void fusion(double tab[N], int debut, int milieu, int fin);

int main() {
    double tab[N];
    double d;
    int index;
    int n;

    printf("Combien de valeurs à trier : ");
    scanf("%d", &n);

    printf("Donner les valeurs à trier : ");
    for (int i = 0; i < n; i++) {
        scanf("%lg", &tab[i]);
    }

    printf("\n---- Valeurs à trier ----\n");
    Affichage(tab, n);

    tri_fusion(tab, 0, n-1);

    printf("\nTableau trié:\n");
    Affichage(tab, n);

    printf("Vous cherchez : ");
    scanf("%lg", &d);

    index = recherche_dichotomique(tab, n, d);

    if (index < 0) {
        printf("L'élément %lg n'a pas été trouvé\n", d);
    } else {
        printf("%lg a été trouvé à l'index %d\n", d, index);
    }

    return EXIT_SUCCESS;
}

void Affichage(double tab[N], int n) {
    for (int i = 0; i < n; i++) {
        printf(" %lg ", tab[i]);
    }
    printf("\n");
}

void tri_bulles(double tab[N], int n) {
    int permutation = TRUE;
    double temp;
    int i, m = 0;

    while (permutation && m < n - 1) {
        permutation = FALSE;
        Affichage(tab, n);

        for (i = n - 1; i > m; i--) {
            if (tab[i - 1] > tab[i]) {
                temp = tab[i - 1];
                tab[i - 1] = tab[i];
                tab[i] = temp;
                permutation = TRUE;
            }
        }
        m++;
    }
}

int recherche_dichotomique(double tab[N], int n, double d) {
    int index = -1;
    int debut = 0;
    int fin = n;
    int milieu;

    while ((index < 0) && (debut != fin)) {
        milieu = (debut + fin) / 2;

        if (tab[milieu] == d) {
            index = milieu;
        } else if (tab[milieu] < d) {
            debut = milieu + 1;
        } else {
            fin = milieu;
        }
    }

    return index;
}

void tri_selection(double tab[N], int n){
	int i, j;
	double temp_v;
	int temp_i;
	
	for (i=0; i<n-1; i++){
		temp_v = tab[i];
		temp_i = i;
		for (j=i+1; j<n; j++){
			if (tab[j] < temp_v){
				temp_v = tab[j];
				temp_i = j;
			}
		}
		tab[temp_i] = tab[i];
		tab[i] = temp_v;
		
	}
	
}


void tri_insertion(double tab[N], int n){
	
	int i;
	int permutation;
	int m;
	double temp;
	
	for (i=1; i<n; i++){
	
		permutation=TRUE;
		m=i;
		
		while ((permutation) && (m > 0)){
			permutation=FALSE;
			if (tab[m] < tab[m - 1]){
				temp = tab[m - 1];
				tab[m - 1] = tab[m];
				tab[m] = temp;
				permutation = TRUE;
			}
			m -=1;
		}
	
	}
	
}

void tri_fusion(double tab[N], int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        tri_fusion(tab, debut, milieu);
        tri_fusion(tab, milieu + 1, fin);

        fusion(tab, debut, milieu, fin);
    }
}


void fusion(double tab[N], int debut, int milieu, int fin) {
	    int n1 = milieu - debut + 1;
	    int n2 = fin - milieu;

	    double L[n1], R[n2];
		
	    int i, j;
	    
	    for (i = 0; i < n1; i++)
		L[i] = tab[debut + i];
	    for (j = 0; j < n2; j++)
		R[j] = tab[milieu + 1 + j];

	    i = 0, j = 0;
	    int k = debut;

	    while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
		    tab[k] = L[i];
		    i++;
		} else {
		    tab[k] = R[j];
		    j++;
		}
		k++;
	    }

	    while (i < n1) {
		tab[k] = L[i];
		i++;
		k++;
	    }

	    while (j < n2) {
		tab[k] = R[j];
		j++;
		k++;
	    }
}


