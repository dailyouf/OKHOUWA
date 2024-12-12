#include <stdlib.h>
#include <stdio.h>

double puissance(double x, unsigned n);

double puissance_rec(double x, unsigned n);

double puissance_rec_ter_aux(double x, unsigned n, double res);
double puissance_rec_ter(double x, unsigned n);

int main(){

	return EXIT_SUCCESS;

}

double puissance(double x, unsigned n){
	
	int i;
	
	if (0==n) return 1;
	
	for (i=1; i<n; i++){
		x *= x;
	}
	
	return x;
}

double puissance_rec(double x, unsigned n){
	
	if (0==n) return 1;
	
	return x * puissance_rec(x, n-1);	
	
}

double puissance_rec_ter_aux(double x, unsigned n, double res){
	
	if (0==n) return res;
	
	return puissance_rec_ter_aux(x, n-1, res * x);	
	
}

double puissance_rec_ter(double x, unsigned n){
	return puissance_rec_ter_aux(x, n, 1);
}
