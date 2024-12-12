#include <stdlib.h>
#include <stdio.h>

int trouver_ecart_maximal_recursif(int tableau[], int debut, int fin) {
    // Cas de base : si le tableau contient moins de deux éléments, l'écart maximal est 0
    if (fin - debut < 2) {
        return 0;
    } else {
        // Trouver l'écart maximal dans les deux moitiés du tableau
        int milieu = (debut + fin) / 2;
        int ecart_max_gauche = trouver_ecart_maximal_recursif(tableau, debut, milieu);
        int ecart_max_droite = trouver_ecart_maximal_recursif(tableau, milieu + 1, fin);
        
        // Trouver le minimum et le maximum dans les deux moitiés
        int min_gauche = tableau[debut];
        int max_gauche = tableau[debut];
        int min_droite = tableau[milieu];
        int max_droite = tableau[milieu];
        
        for (int i = debut + 1; i < milieu; i++) {
            if (tableau[i] < min_gauche) {
                min_gauche = tableau[i];
            } else if (tableau[i] > max_gauche) {
                max_gauche = tableau[i];
            }
        }
        
        for (int i = milieu + 1; i < fin; i++) {
            if (tableau[i] < min_droite) {
                min_droite = tableau[i];
            } else if (tableau[i] > max_droite) {
                max_droite = tableau[i];
            }
        }
        
        // Calculer l'écart maximal entre les deux moitiés et retourner le maximum
        int ecart_max_entre_halves = max_droite - min_gauche;
        return ecart_max_entre_halves > ecart_max_gauche ? ecart_max_entre_halves : ecart_max_gauche > ecart_max_droite ? ecart_max_gauche : ecart_max_droite;
    }
}

int main() {
    int tableau[] = {7, 1, 5, 3, 9, 2, 8};
    int taille = sizeof(tableau) / sizeof(tableau[0]);
    int ecart_maximal = trouver_ecart_maximal_recursif(tableau, 0, taille);
    printf("L'ecart maximal entre deux valeurs i et j tel que i < j est : %d\n", ecart_maximal);
    return EXIT_SUCCESS;
}
