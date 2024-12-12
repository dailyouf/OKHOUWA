#include<stdlib.h>
#include<stdio.h>


int main(){
	
	FILE* fp;
	
	fp = fopen("Test.txt", "r");
	
	if (fp==NULL) {
		printf("Ouverture impossible \n");
		return EXIT_FAILURE;
	}
	
	

	
	char c;
	while ((c=getc(fp))!=EOF){
		
		putc(c, stdout);	
		
	}
	
	rewind(fp);
	
	char a[10];
	char b[10];
	fscanf(fp, "%s %s \n", a, b);
	
	int x;
	
	x = fprintf(stdout, "%s %s \n", a, b);
	
	printf("%d \n", x);
	
	fclose(fp);
	
	return EXIT_SUCCESS;

}
