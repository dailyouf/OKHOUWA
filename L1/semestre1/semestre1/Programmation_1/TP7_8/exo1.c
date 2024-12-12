#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Definitions des constantes symboliques
#define TRUE 1
#define FALSE 0
#define NB 10

//déclaration des strucutures
struct carreau_s{
	
	int hauteur;
	int largeur;	
	
	char couleur[NB];

};

struct tablette_s{			
	
	int hauteur_total, largeur_total;
	
	struct carreau_s mes_carreau[NB][NB];
	
};

//Déclarations des fonctions
int partie_perdue(int coinx, int coiny, int corx, int cory);

struct tablette_s joueur(struct tablette_s, int corx, int coty);
struct tablette_s oposant(struct tablette_s, int choice_x, int choice_y);

void affichage(struct tablette_s);

int main(){
	
	// char cote[10];
	int choice_x, choice_y;
	
	int corx, cory;
	int coinx, coiny;
	
	/*Definition du role du joueur*/
	enum role {PLAYER, COMPUTER};
	enum role current_player = PLAYER;
	
	/*initialisation de ma tablette */
	int i, j;
	
	struct carreau_s carreau_noir={1, 1, "NOIR"};
	struct carreau_s carreau_vert={1, 1, "VERT"};
	
	struct tablette_s actual_tab;
	
	actual_tab.hauteur_total = NB;
	actual_tab.largeur_total = NB;
	
	for (i=0; i<NB; i++){
		for (j=0; j<NB; j++){
			actual_tab.mes_carreau[i][j] = carreau_noir;
		}
	}
	
	/*Choix aléatoire de l'emplacement du carreau vert*/
	srand(time(NULL));
	
	coinx = rand() % 10;
	coiny = rand() % 10;
	
	actual_tab.mes_carreau[coinx][coiny] = carreau_vert;
	
	
	/*Boucle du jeu*/
	while (TRUE){
		
		affichage(actual_tab);
		
		if (current_player==PLAYER){
			printf("Veuillez insérer les cordonnées du point à supprimer : \n");
			printf("Cordonnée x : ");
			scanf(" %d \n", &corx);
			printf("Cordonnée y : ");
			scanf(" %d \n", &cory);
			
			actual_tab = joueur(actual_tab, corx, cory);
						
			if (partie_perdue(coinx, coiny, corx, cory)==TRUE){
				break;
			}
			
			current_player = COMPUTER;
				
		}else{	
			choice_x = rand() % 10;
			choice_y = rand() % 10;
			
			actual_tab = oposant(actual_tab, choice_x, choice_y);
			
			if (partie_perdue(coinx, coiny, choice_x, choice_y)==TRUE){
				break;
			}
			
			current_player = PLAYER;
		}
		

		printf("%d \n", current_player);
	
	}
	
	/*Affichage du gagnant*/
	if(current_player == COMPUTER){	
		printf("Vous avez gagné \n");
	}else{
		printf("Vous avez perdu \n");
	}
	
	
	
	return EXIT_SUCCESS;

}

int partie_perdue(int coinx, int coiny, int corx, int cory){
	
	return (coinx == corx) && (coiny == cory);
}

struct tablette_s joueur(struct tablette_s actual_tab, int corx, int cory){
	
	// int i;
	
	struct carreau_s vide = {0, 0, ""};
	
	
	actual_tab.mes_carreau[corx][cory] = vide;
	
	
	/*if (cote[0] == 'l'){
		for (i=0; i<NB; i++){
			actual_tab.mes_carreau[actual_tab.hauteur_total - 1][i] = vide;
		}
		actual_tab.hauteur_total -= 1;
	}else{
		for (i=0; i<NB; i++){
			actual_tab.mes_carreau[i][actual_tab.largeur_total - 1] = vide;
		}
		actual_tab.largeur_total -= 1;	
	}
	*/
	return actual_tab;

}
struct tablette_s oposant(struct tablette_s actual_tab, int choice_x, int choice_y){

	
	// int i;
	
	struct carreau_s vide = {0, 0, ""};
	
	actual_tab.mes_carreau[choice_x][choice_y] = vide;
	/*
	if (choice == 0){
		for (i=0; i<NB; i++){
			actual_tab.mes_carreau[actual_tab.hauteur_total - 1][i] = vide;
		}
		actual_tab.hauteur_total -= 1;
	}else{
		for (i=0; i<NB; i++){
			actual_tab.mes_carreau[i][actual_tab.largeur_total - 1] = vide;
		}
		actual_tab.largeur_total -= 1;	
	}
	*/
	return actual_tab;

}

void affichage(struct tablette_s actual_tab){
	
	// printf("Les dimensions sont : [%d][%d] \n", actual_tab.hauteur_total, actual_tab.largeur_total);
	
	
	int i, j;
	// 		char c;
	
	for (i=0; i<actual_tab.hauteur_total; i++){
		for (j=0; j<actual_tab.largeur_total; j++){
			if(actual_tab.mes_carreau[i][j].couleur[0] == 'N'){
				printf("#");
			}else if(actual_tab.mes_carreau[i][j].couleur[0] == 'V'){
				printf("V");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	
	}
}



/*(actual_tab.mes_carreau[1][0].hauteur==0 && actual_tab.mes_carreau[1][0].largeur==0) 
	|| (actual_tab.mes_carreau[0][1].hauteur == 0 && actual_tab.mes_carreau[1][0].largeur==0) */
//
