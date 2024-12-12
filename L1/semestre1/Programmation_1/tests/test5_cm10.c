#include <stdlib.h>
#include <stdio.h>

int main(){

	FILE * fp;
	int c;
	
	if ((fp=fopen("my_file.txt", "w+"))==NULL){
		exit(1);
	
	}else{
		
		fprintf(fp, "%s \n %s \n %s \n", "BONJOUR", "HELLO WORLD", "Je m'appelle YOUCEF");
		
		while((c=getc(fp))!=EOF){
			putchar(c);
		}
		
		
		fclose(fp);
	
	}


	return EXIT_SUCCESS;

}


