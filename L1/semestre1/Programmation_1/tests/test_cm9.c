#include <stdlib.h>
#include <stdio.h>


int main(){


	
	enum bool{False=0, True=1};
	
	typedef enum bool bool;
	
	bool runing;
	
	printf("%d \n", runing);
	
	runing = 2;
	
	printf("%d \n", runing);
	
	return EXIT_SUCCESS;

}
