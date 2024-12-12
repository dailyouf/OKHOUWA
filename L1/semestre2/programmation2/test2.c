#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	
	srand(time(NULL));
	
	int tab[20];
	
	for (int i=0; i<20; i++) {
		tab[i] = rand() % 10;
		printf("%d \n", tab[i]);
	}
	

	return EXIT_SUCCESS;
}
