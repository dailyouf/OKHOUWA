#include<stdlib.h>
#include<stdio.h>

void affiche_bin_rev(unsigned n);

void affiche_bin(unsigned n);

void affiche_bin_rec(unsigned n);

int main(){
	
	unsigned n;
	scanf("%u", &n);
	
	
	affiche_bin_rev(n);
	affiche_bin(n);
	affiche_bin_rec(n);
	printf("\n");
		
	return EXIT_SUCCESS;	
	
}


void affiche_bin_rev(unsigned n){
	
	do{
		printf("%u", n % 2);	
		n /= 2;	
	}while (n > 0);
	
	printf("\n");
	
}

void affiche_bin(unsigned n){
	
	char tab[33];
	unsigned i=0;
	
	do{	
		tab[i++] = '0' + (n % 2);
		n /= 2;
	
	}while (n > 0);
	
	tab[i] = '\0';

	while (i > 0){

		printf("%c", tab[--i]);

	}
	
	printf("\n");
	
}

void affiche_bin_rec(unsigned n){

	if ((n == 0) || (n == 1)){
		printf("%u", n);
		return;
	}else{
		
		affiche_bin_rec(n / 2);
		printf("%u", n % 2);
		
	}
	
}

	/*
	-wfatal-errors => arrete la compilation à la premiere erreur rencontrée
	-Wall => avoir tout les warning 
	-pedantic => avoir les commentaires du compilateur (pas très utile)
	*/
