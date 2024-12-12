#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(){

	enum test{A, B, C, D, E};
	
	typedef enum test epsilon;
	
	epsilon var=E;
	
	
	
	printf("%d \n", (var==E));

	
	srand(time(NULL));
	
	printf("%d \n", rand() % 100);
	
	char c, d;
	scanf(" %c \n", &c);
	scanf(" %c \n", &d);
	printf("Hello my %c %c \n", c, d);
	

	return EXIT_SUCCESS;

}



