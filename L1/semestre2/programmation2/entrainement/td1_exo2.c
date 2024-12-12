#include <stdlib.h>
#include <stdio.h>

#define N 25

void affiche_bin_rev(unsigned n);
void affiche_bin(unsigned n);
void affiche_bin_rec(unsigned n);

int main(){

	
	affiche_bin_rev(10);
	affiche_bin(10);
	affiche_bin_rec(10);
	printf("\n");
	
	return EXIT_SUCCESS;	
	
}

void affiche_bin_rev(unsigned n){

	if (0==n) {
		printf("%u", n);
	}
		
	while (n > 0) {
		printf("%u", n % 2);
		n /= 2;
	}
	
	printf("\n");
}

void affiche_bin(unsigned n){

	char tab[N];
	
	int i=0;

	if (0==n) {
		tab[i] = '0';
	}
		
	while (n > 0) {
		tab[i] = '0' + (n % 2);
		n /= 2;
		i++;
	}
	
	while (i > 0) {
		i--;
		printf("%c", tab[i]);
	}
	
	
	printf("\n");
}


void affiche_bin_rec(unsigned n){

	if (0==n || 1==n) {
		printf("%u", n);
	}
	
	else {
		affiche_bin_rec(n / 2);	
		printf("%u", n % 2);
	}
	
}

