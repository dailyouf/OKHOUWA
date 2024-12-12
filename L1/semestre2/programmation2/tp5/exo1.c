#include <stdio.h>
#include <stdlib.h>

void echange_pointeur(int **p, int *q)
{
	int * tmp;
	
	/* Affichage de l'adresse de p (dans la fonction echange_pointeur) */
	printf("adresse de p dans la fonction = %p\n", &p);
	/* Affichage de l'adresse de p dans la fonction */
	printf("adresse de q dans la fonction = %p\n", &q);
	/* Affichage de l'adresse de l'entier pointé par p (dans la fonction echange_pointeur) */
	printf("adresse de l'entier pointé par p avant réaffectation dans echange_pointeur  = %p\n", p);
	/* Affichage de l'adresse de l'entier pointé par q (dans la fonction echange_pointeur) */
	printf("adresse de l'entier pointé par q avant réaffectation dans echange_pointeur = %p\n", q);
	
	/* Réaffectation de p */
	tmp = *p;
	*p = q;
	q = tmp;
	
	/* Affichage de l'adresse de p après réaffectation (dans la fonction echange_pointeur) */
	printf("adresse de p dans la fonction après réaffectation dans echange_pointeur = %p\n", &p);
	/* Affichage de l'adresse de l'entier pointé par p après réaffectation (dans la fonction echange_pointeur) */
	printf("adresse de l'entier pointé par p après réaffectation dans echange_pointeur = %p\n", p);
}

int main(void)
{
  	int *p;  /* p est un pointeur sur un entier */
	int *q;  /* q est un pointeur sur un entier */
	int i = 1, j = 2;
	
	/* Affichage de l'adresse de p avant échange (dans la fonction principale) */
	printf("adresse de p avant échange = %p\n", &p);
	/* Affichage de l'adresse de q avant échange (dans la fonction principale) */
	printf("adresse de q avant échange = %p\n", &q);
	/* Affichage de l'adresse de i avant échange (dans la fonction principale) */
	printf("adresse de i avant échange = %p\n", &i);
	/* Affichage de l'adresse de j avant échange (dans la fonction principale) */
	printf("adresse de j avant échange = %p\n", &j);

	/* Initialisation de p et q */
	p = &i;
	q = &j;
	
  	/* Affichage de l'adresse de l'entier pointé par p avant échange (dans la fonction principale) */
	printf("adresse de la variable pointée par p avant échange = %p\n", &(*p));
	/* Affichage de la valeur de l'entier pointé par p avant échange (dans la fonction principale) */
	printf("valeur de la variable pointée par p avant échange = %d\n", *p);
	
	/* Appel de la fonction echange_pointeur */
	echange_pointeur(&p,q);
	
	/* Affichage de l'adresse de p après échange (dans la fonction principale) */
	printf("adresse de p après échange = %p\n", &p);
	/* Affichage de l'adresse de l'entier pointé par p après échange (dans la fonction principale) */
	printf("adresse de la variable pointée par p après échange = %p\n", p);
	/* Affichage de la valeur de l'entier pointé par p après échange (dans la fonction principale) */
	printf("valeur de la variable pointée par p après échange = %d\n", *p);
	/* Affichage de l'adresse de l'entier pointé par q après échange (dans la fonction principale) */
	printf("adresse de la variable pointée par q après échange = %p\n", q);
	
	

	return EXIT_SUCCESS;
}

