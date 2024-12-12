#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
	
	
	printf("%lg \n", log(10));	
		
	int x;
	
	scanf(" %d \n", &x);
	
	switch (x){
	
		case 1:
			printf("1 \n");

 		case 2:
 			printf("2 \n");
		
		default:
			printf("Rien \n");
	
	}
	return EXIT_SUCCESS;

}
