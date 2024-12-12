#include <stdlib.h>
#include <stdio.h>


int main(){
	
	int n;
	int i, j;
	char s[255];
		
	
	do{
		scanf("%u", &n);
	}while(n > 10);

	j = 'a';
	
	for (i=0; i < n*n; i++){
		for(j=0; j < n; j++){
			s[i++] = '*';
		}
		for(j=0; j < n; j++){
			s[i++] = '\n';
			s[i++] = '*';
		}
		for(j=0; j < n; j++){
			s[i++] = '*';
		}
		for(j=0; j < n; j++){
			s[i++] = '\n';
			s[i++] = '*';
		}

	}
	
	s[i] = '\0';
	
	
	printf("%s", s);
	
	return EXIT_SUCCESS;

}
