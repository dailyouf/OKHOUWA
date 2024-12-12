/* Declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* pour EXIT_SUCCESS */
#include <stdio.h> /* pour printf() */

/* Declaration des constantes et types utilisateur */

/* Declaration des fonctions utilisateur */
int maximum(int x, int y);
int puissance(int b, int e);
 
/* Fonction principale */
int main()
{
    /* Declaration et initialisation des variables */
    int x = 4;
    int y = 5;
    int z;

    z = maximum(x, y);
    printf("maximum(%d, %d) = %d\n", x, y, z);

    z = maximum(10, -3);
    printf("maximum(10, -3) = %d\n", z);

    z = maximum(x, x);
    printf("maximum(%d, %d) = %d\n", x, x, z);

    z = puissance(x, y);
    printf("puissance(%d, %d) = %d\n", x, y, z);

    /* Valeur fonction */
    return EXIT_SUCCESS;
}

/* Definition des fonctions utilisateur */
int maximum(int a, int b)
{
    if (a < b)
    {
	return b; /* termine l'appel */
    }
    /* a >= b */
    return a;
}

int puissance(int base, int exposant)
{
    int res = 1; /* accumulateur de produit */
    int i; /* var de boucle */
    
    for (i = 0; i < exposant; i = i + 1) /* faire exposant fois */
    {
	res = res * base; /* multiplication par base */	
    }
    return res;
}
