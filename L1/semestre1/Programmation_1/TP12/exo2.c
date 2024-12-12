#include<stdlib.h>
#include<stdio.h>

int factorielle(int n);
double e_approche(int n);


int main(){

	printf(" %lg \n", e_approche(20));

	return EXIT_SUCCESS;

}

int factorielle(int n){

	if (n < 0){
		printf("Veuillez entrer un nombre positif \n");
		return 0;
	}
	
	if ((n == 0) || (n == 1)){
		return 1;
	}else {
		return n * factorielle(n - 1);	
	}
	
}



double e_approche(int n){
	int i;
	double s;
	
	for (i=0; i<n+1; i++){
		s += 1.0 / factorielle(i);
	}
	
	return s;
}
