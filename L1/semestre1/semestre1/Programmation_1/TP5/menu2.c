#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define NB_MAX 100


int si_premier(int nb);

void deviner_nombre();

int cube(int);

int est_majeur(int age);

int somme(int n);

void afficher_rectangle(int largeur, int hauteur);

int saisie_utilisateur();

int main(){
	
	afficher_rectangle(10, 10);
	printf("%d \n", cube(6));
	printf("%d \n", est_majeur(16));
	printf("%d \n", somme(10));
	printf("%d \n", saisie_utilisateur());
	
	int nb, choix;
	
	
	do{
		printf("****************** MENU ****************** \n \
*                                        * \n \
*     1) Tester si un nombre est premier * \n \
*     2) Deviner un nombre               * \n \
*     0) QUITTER                         * \n \
*                                        * \n \
************************** votre choix : ");		
		
		scanf(" %d \n", &choix);		
		
		if (choix == 0){
			printf("FIN DU PROGRAMME \n");
			break;
		}	
		
		else if (choix == 1){
			/*printf("premier : non disponible \n");*/
			printf("Entrez votre nombre à tester: ");
			scanf(" %d \n", &nb);
	
			if (si_premier(nb) == TRUE){
				printf("Le nombre est premier \n");
			}else{
				printf("Le nombre n'est pas premier \n");
			}
			
		}else if (choix == 2){
			/*printf("deviner un nombre : non disponible \n");*/
			deviner_nombre();
			
		}else {
			printf("choix non disponible \n");
			continue;
		}
		
	}while (TRUE);


	return EXIT_SUCCESS;

}


int si_premier(int nb){
	int i, res=TRUE;
	for (i=1; i <= nb; i++){
		// printf("%d ", nb % i);
		if (nb % i == 0){
			res = FALSE;
			break;
		}
	}
	// printf(" %d \n", res);
	return res;
}


void deviner_nombre(){
 	int nb, choix;
	
	srand(time(NULL));
	
	nb = rand() % (NB_MAX + 1);
	
	// printf(" %d \n", nb);
	
	do {
		scanf(" %d", &choix);
		
		if (nb < choix){
			printf("Plus petit \n");	
		}
		if (nb > choix){
			printf("Plus grand \n");
		}
	
	}
	while (choix != nb);
	
	printf("Félecitation \n");
 
}


int cube(int x){

	return x * x * x;	

}

int est_majeur(int age){

	return (age >= 18);

}

int somme(int n){
	int s, i;
	
	for (i=1; i<=n; i++){
		s +=i;
	
	}
	return s;
}


void afficher_rectangle(int l, int h){

	int i, j;
	
	for (i=1; i<=h; i++){
		if (i==1 || i ==h){
			for (j=0; j<l; j++){
				printf("*");
			} 
		}else{	
			printf("*");
			for (j=1; j<l-1; j++){
				printf(" ");
			}
			printf("*");
		}
		printf("\n");
	
	}
}

int saisie_utilisateur(){
	int n;


	printf("Veuillez saisir un entier :");
	scanf(" %d \n", &n);
	
	return n;

}



