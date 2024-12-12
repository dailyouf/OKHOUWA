#include <stdlib.h>
#include <stdio.h>



int main(){

	int a, b, a_ET_b, a_OU_b, NON_a, NON_b, NON_a_ET_b;
	
	printf("entrez deux valeurs booleennes : ");
	scanf(" %d %d \n", &a, &b);

	a_ET_b = (a && b) ? 1 : 0;
	
	a_OU_b = (a || b) ? 1 : 0;
	
	/*ici y'a plusieurs façons de faire*/	
	NON_a = !a;
	
	NON_b = (b) ? 0 : 1;
	/*elles sont équivalentes*/
	NON_b = b ? 0 : 1;
	
	NON_a_ET_b = (!a && b) ? 1 : 0;
	
	printf("a\tb\ta ET b\ta OU b\tNON a\tNON b\tNON a ET b\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d \n", a, b, a_ET_b, a_OU_b, NON_a, NON_b, NON_a_ET_b);
	
	return EXIT_SUCCESS;

}
