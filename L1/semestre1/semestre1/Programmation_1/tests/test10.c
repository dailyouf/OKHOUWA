#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define N 100

#define nb_velo 9


#define TRUE 1
#define FALSE 0

struct bike {

	char marque[N];
	char immatriculation[N];
	int batterie;
	int loue; 

};

int affichage_menu();

void louer_velo(char immatriculation[N], struct bike liste_velo[nb_velo]);
void retour_velo(char immatriculation[N], struct bike liste_velo[nb_velo]);
void etat_velo(char immatriculation[N], struct bike liste_velo[nb_velo]);

int main(){

	int choix;

	do{
		choix = affichage_menu();
	
	}while(choix >= 0 && choix <= 4);

	
	
	
	return EXIT_SUCCESS;


}


int affichage_menu(){
	
	int choix;
	
	printf("\t MENU \n");
	printf("\t ==== \n \n");
	
	printf("1: louer Vélo \n");
	printf("2: Retour Vélo \n");
	printf("3: Etat Vélo \n");
	printf("4: Etat de l'ensemble des Vélos \n");
	printf("0: Fin Programme \n");
	
	printf("\t Votre choix: ");
	scanf(" %d \n", &choix);	
	
	return choix;
}

void louer_velo(char immatriculation[N], struct bike liste_velo[nb_velo]){


	int i;
	int state=FALSE;
	
	for (i=0; i<nb_velo; i++){
		
		if (strcmp(liste_velo[i].immatriculation, immatriculation) && liste_velo[i].loue == FALSE && liste_velo[i].batterie == 100){
			liste_velo[i].loue = TRUE;
			liste_velo[i].batterie = 0;
			state=TRUE;
			break;
		}
	}
	
	if (!state){
		printf("Il y'a erreur \n");
	}
}

void retour_velo(char immatriculation[N], struct bike liste_velo[nb_velo]){


	int i;
	int state=FALSE;
	
	for (i=0; i<nb_velo; i++){
		
		if (strcmp(liste_velo[i].immatriculation, immatriculation) && liste_velo[i].loue == TRUE){
			liste_velo[i].loue = FALSE;
			printf("IL reste combien de batterie ? \n");
			scanf(" %d \n", &liste_velo[i].batterie);
			state=TRUE;
			break;
		}
	}
	
	if (!state){
		printf("Il y'a erreur \n");
	}
}


void etat_velo(char immatriculation[N], struct bike liste_velo[nb_velo]){


	int i;
	int state=FALSE;
	
	for (i=0; i<nb_velo; i++){
		
		if (strcmp(liste_velo[i].immatriculation, immatriculation)){
			printf("%s %s %2d% %s \n", liste_velo[i].marque, liste_velo[i].immatriculation, liste_velo[i].batterie, (liste_velo[i].immatriculation) ? "Loué" : "Disponible");
			state=TRUE;
			break;
		}
	}
	
	if (!state){
		printf("Il y'a erreur \n");
	}
}





