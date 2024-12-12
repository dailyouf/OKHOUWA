#include <stdlib.h>
#include <stdio.h>

double produit_tab(double * tab, int n);

double produit_tab_rec(double * tab, int n);

double produit_tab_rec_ter(double * tab, int n);
double produit_tab_rec_ter_aux(double * tab, int n, double res);

int main(){

	double tab[5]={1, 2, 3, 4, 5};
	
	printf("%lg \n", produit_tab(tab, 5));	
	printf("%lg \n", produit_tab_rec(tab, 5));
	printf("%lg \n", produit_tab_rec_ter(tab, 5));
	
	return EXIT_SUCCESS;

}

double produit_tab(double * tab, int n){
	
	int i;
	double res=1;
	
	for (i=0; i<n; i++){
		res *= tab[i];
	}
	
	return res;
}

double produit_tab_rec(double * tab, int n){

	if (0==n) return 1;
	
	return tab[0] * produit_tab_rec(tab + 1, n - 1);
}


double produit_tab_rec_ter_aux(double * tab, int n, double res){
	if (0==n) return res;
	
	return produit_tab_rec_ter_aux(tab + 1, --n, res * tab[0]);
}

double produit_tab_rec_ter(double * tab, int n){
	
	return produit_tab_rec_ter_aux(tab, n, 1);
	
}
