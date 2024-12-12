#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
	
	int nbc=0, nbm=1, nbl=1;
	char c;
	
	FILE * fp1;
	FILE * fp2;
	
	FILE * fp3;
	fp3 = fopen("text3.txt", "w");
	

	
	if (argc != 4) {
		printf("Nombre d'arguments insufisants \n");
		exit(1);
	}
	
	if ((strcmp(argv[3], "c") && strcmp(argv[3], "m")) && strcmp(argv[3], "l")) {
		printf("Troisième argument nom conforme \n");
		exit(1);	
	}
	
	if ((fp1=fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Erreur à l'ouverture du fichier text1");
		exit(1);
	}
	
	
	if ((fp2=fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "Erreur à l'ouverture du fichier text2");
		exit(1);
	}
	
	
	printf("Affichage pour le fichier 1\n");
	while (!feof(fp1)) {
		c = fgetc(fp1);
		if (c=='\n') {
			nbl++;
		} else if (c==' '){
			nbm++;
		}
		
		fprintf(fp3, "%c", c);
		nbc++;
	}
	
	printf("Le nombre de caractères est: %d \nLe nombre de mots est: %d \nLe nombre de lignes est: %d \n", nbc, nbm, nbl);
	
	fseek(fp3, -1 * sizeof(char), SEEK_END);
	
	printf("\nAffichage pour le fichier 2\n");	
	nbc=0, nbm=0, nbl=0;
	while (!feof(fp2)) {
		c = fgetc(fp2);
		if (c=='\n') {
			nbl++;
		} else if (c==' '){
			nbm++;
		}
		fprintf(fp3, "%c", c);
		nbc++;
	}
	printf("Le nombre de caractères est: %d \nLe nombre de mots est: %d \nLe nombre de lignes est: %d \n", nbc, nbm, nbl);
	
	
	
	rewind(fp3);
	
	printf("\nAffichage pour le fichier 3\n");
		
	nbc=0, nbm=0, nbl=0;
	
	while ((c = fgetc(fp3)) != EOF) {
		if (c=='\n') {
			nbl++;
		} else if (c==' '){
			nbm++;
		}
		nbc++;
	}
	
	switch (argv[3][0]) {
	
		case 'c':
			printf("Le nombre de caractères est: %d \n", nbc);
			break;
		case 'm':
			printf("Le nombre de mots est: %d \n", nbm);
			break;
		case 'l':
			printf("Le nombre de lignes est: %d \n", nbl);
			break;	
	}	
	
	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	
	return EXIT_SUCCESS;

}
