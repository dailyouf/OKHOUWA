#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int calcul_jj(int j, int m, int a){
	
	int jj;
	double x1, x2, x3, x4;
	
	if (m > 2) {
		x1 = a;
		x2 = m;
	}else{
		x1 = a - 1;
		x2 = m + 12;		
	}
	
	if ((a>1582) || (a==1582 && m>10) || (a==1582 && m==10 && j>=15)){
		x3 = floor(x1 / 100);
		x4 = 2 - x3 + floor(x3 / 4); 
	}else{
		x4 = 0;
	}
	
	jj = x4 + j + floor(30.6001 * (x2 + 1)) + floor(365.25 * x1) + 1720994.5;
	
	return jj;
}

int main(){
	
	double cycle_physique, cycle_emotionnel, cycle_intellectuel, moyenne;
	int N;
	int j, m, a;
	
	printf("Entrez la date: ");
	scanf("%d %d %d \n", &j, &m, &a);
	
	N = calcul_jj(j, m, a);
	
	cycle_physique = sin(2 * M_PI * N / 23);
	cycle_emotionnel = sin(2 * M_PI * N / 28);
	cycle_intellectuel = sin(2 * M_PI * N / 33);

	moyenne = (cycle_physique + cycle_emotionnel + cycle_intellectuel) / 3;
	
	if (moyenne >= 0){
		printf("la période est favorable \n");
	}else {
		printf("la période est défavorable \n");
	}

	return EXIT_SUCCESS;

}
