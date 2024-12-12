#include <stdlib.h>
#include <stdio.h>



int main(){

	char tab[4];
			
	int i;
	
	for (i=0; i<4; i++){
		tab[i] = 'a' + i;	
	}
	
	for (i=0; i<5; i++){
		printf("%c \n", tab[i]);	
		printf("%d \n \n", tab[i]);	
	}



	return EXIT_SUCCESS;

}
