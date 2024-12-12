#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*commençant par déclarer les constantes de notre programme relatives aux volumes*/
#define S_PICINE 12
#define V_CORPS 12

#define V_PIANO 12
#define V_COFFRE_FORT 12
#define V_ESPION 12


int main(){
	
	/*introduisant maintenant nos variables temporelles*/
	int t0 = time(NULL); 

	int t15 = 15 * 60;
	int t30 = 30 * 60;
	
	int difference_min=0, difference_sec=0;
	
	/*introduisant aussi nos variables en rapport avec les volumes variants*/
	float h_eau=0, v_eau=0, v_picine_occupe=0, v_objet=0;
	int etat_james = 1;
	
	while (time(NULL) - t0 < 3600){
		
		if (time(NULL) - difference_sec >= 1) {
			difference_sec = time(NULL);
			v_eau += 0.5;
			
			if ((t15 < time(NULL) - t0) && (time(NULL) - t0< t30)){
				v_eau -= 0.37 / 1000;
			}
				
		}
		
		
		switch (time(NULL) - t0){
			case 5 * 60:
				v_objet += V_PIANO;
				break;
			case 25 * 60:
				v_objet += V_COFFRE_FORT;
				break;
			case 40 * 60:
				v_objet += V_ESPION;
				break;
		}
		
		v_picine_occupe = v_eau + V_CORPS + v_objet;
		
		h_eau = v_picine_occupe / S_PICINE;
		
		if (h_eau > 1.82){
			etat_james = 0;
		}
		
	
		if (time(NULL) - difference_min > 60) {
			difference_min = time(NULL);
			printf("%lg", h_eau);
		}
		

		
	
	
	}
	
	printf("James est %s \n", (etat_james) ? "Vivant" : "Morts");


	return EXIT_SUCCESS;
	

}
