#include <stdlib.h>
#include <stdio.h>

int main(){

	int i;

	char tab[4]="Hello";
	printf("%s \n", tab);
	
	int serie[5];
	serie[0] = 0;

	for (i = 0; i < 4; i = i + 1){
		serie[i+1] = i + serie [i];
	}
	
	for (i=0; i<5; i++){
		printf(" %d", serie[i]);
	}
	
	printf("\n");

}
