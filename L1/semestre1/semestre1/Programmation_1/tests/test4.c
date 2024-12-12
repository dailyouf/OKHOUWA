#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(){

	printf("%c \n", tolower('D'));

	char s1[]="Hello \n";
	char s2[]="Hello1";
	printf("%ld \n", strlen(s1));	
	
	printf("\n \n");
	
	enum couleur{ROUGE = 2, VERT = 0, ORANGE = 1, BLEU, YELLOW} ;
	enum couleur etat_feu;
	printf("%d \n", etat_feu);
	
	int i;
	printf("%d \n", i);
	
	
	printf("\n \n");
	
	char c = getc(stdin);
	
	putc(c, stdout);
	
	putc('\n', stdout);
	
	return EXIT_SUCCESS;

}
