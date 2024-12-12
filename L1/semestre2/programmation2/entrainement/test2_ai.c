#include <stdio.h>

// Fonction récursive pour calculer la somme des éléments d'un tableau
int sommeTableau(int tableau[], int taille) {
    if (taille == 1){
    	return tableau[0];
    }
    // Cas récursif : diviser le tableau en deux parties et récursivement calculer la somme de chaque partie
    else {
        int moitie = taille / 2;
        return sommeTableau(tableau, moitie) + sommeTableau(tableau + moitie, taille - moitie);
    }
}

int main() {
    int tableau[] = {1, 2, 3, 4, 5};
    int taille = sizeof(tableau) / sizeof(tableau[0]);
    int somme = sommeTableau(tableau, taille);
    printf("La somme des éléments du tableau est : %d\n", somme);
    return 0;
}
