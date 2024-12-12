#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int jour;
    char mois[20];

    while (1) {
        printf("Donnez votre jour et mois de naissance (ex: 25 janvier) : \n");
        scanf("%d %s", &jour, mois);

        if (jour < 0 || jour > 31) {
            printf("*** Veuillez saisir un jour valide *** \n");
            continue;
        }

        printf("%d %s \n", jour, mois);

        if ((strcmp(mois, "mars") == 0 && jour >= 21) || (strcmp(mois, "avril") == 0 && jour <= 20)) {
            printf("Bélier \n");
        } else if ((strcmp(mois, "avril") == 0 && jour >= 21) || (strcmp(mois, "mai") == 0 && jour <= 21)) {
            printf("Taureau \n");
        } else if ((strcmp(mois, "mai") == 0 && jour >= 22) || (strcmp(mois, "juin") == 0 && jour <= 21)) {
            printf("Gémeaux \n");
        } else if ((strcmp(mois, "juin") == 0 && jour >= 22) || (strcmp(mois, "juillet") == 0 && jour <= 22)) {
            printf("Cancer \n");
        } else if ((strcmp(mois, "juillet") == 0 && jour >= 23) || (strcmp(mois, "aout") == 0 && jour <= 22)) {
            printf("Lion \n");
        } else if ((strcmp(mois, "aout") == 0 && jour >= 23) || (strcmp(mois, "septembre") == 0 && jour <= 22)) {
            printf("Vierge \n");
        } else if ((strcmp(mois, "septembre") == 0 && jour >= 23) || (strcmp(mois, "octobre") == 0 && jour <= 22)) {
            printf("Balance \n");
        } else if ((strcmp(mois, "octobre") == 0 && jour >= 23) || (strcmp(mois, "novembre") == 0 && jour <= 21)) {
            printf("Scorpion \n");
        } else if ((strcmp(mois, "novembre") == 0 && jour >= 22) || (strcmp(mois, "decembre") == 0 && jour <= 21)) {
            printf("Sagittaire \n");
        } else if ((strcmp(mois, "decembre") == 0 && jour >= 22) || (strcmp(mois, "janvier") == 0 && jour <= 20)) {
            printf("Capricorne \n");
        } else if ((strcmp(mois, "janvier") == 0 && jour >= 21) || (strcmp(mois, "fevrier") == 0 && jour <= 19)) {
            printf("Verseau \n");
        } else if ((strcmp(mois, "fevrier") == 0 && jour >= 20) || (strcmp(mois, "mars") == 0 && jour <= 20)) {
            printf("Poissons \n");
        } else {
            printf("*** Erreur de nom de mois ou date *** \n");
        }
    }

    return EXIT_SUCCESS;
}



/* #include <stdlib.h>
#include <stdio.h>
#include <string.h>




int main(){
	
	int jour;
	
	
	char mois[20];
	
	
	while (1){
		printf("donnez vos jour et mois de naissance ? \n");
	
		scanf("%d %s \n", &jour, mois);
	
		if(jour<0 || jour>31) {
			printf("*** Veuillez saisir un jour valide *** \n");
			continue;
		}
		
		printf("%d %s \n", jour, mois);
		
		if ((strcmp(mois, "mars") && jour>=21) || (strcmp(mois, "avril") && jour<=20)){
			printf("Bélier \n");
		}else if ((strcmp(mois, "avril") && jour>=21) || (strcmp(mois, "mai") && jour<=21)){
			printf("Taureau \n");
		}else if ((strcmp(mois, "mai") && jour>=22) || (strcmp(mois, "juin") && jour<=21)){
			printf("Gémeaux \n");
		}else if ((strcmp(mois, "juin") && jour>=22) || (strcmp(mois, "juillet") && jour<=22)){
			printf(" Cancer \n");
		}else if ((strcmp(mois, "juillet") && jour>=23) || (strcmp(mois, "aout") && jour<=22)){
			printf(" Lion \n");
		}else if ((strcmp(mois, "aout") && jour>=23) || (strcmp(mois, "septembre") && jour<=22)){
			printf(" Vierge \n");
		}
		else{
			printf("*** erreur de nom de mois *** \n");
		}
	}
	


	return EXIT_SUCCESS;

}

*/
