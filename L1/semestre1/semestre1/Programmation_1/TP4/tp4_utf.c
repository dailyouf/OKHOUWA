#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int calcul_jj(j, m , a){
	
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

/*int date_vers_jj(jj){
	
	
	return 
}	
*/



int main(){

	int naissance;
	
	int j, m, a;
	
	printf("Entrez la date: ");
	scanf(" %d %d %d \n", &j, &m, &a);
	
	naissance = calcul_jj(j, m, a);
	/*janvier2000 = calcul_jj(1, 1, 2000); */
	
	int jj = naissance + 10000;
	jj += 0.5;
	
	int z, aa, b, c, d, e;
	
	double f;

	z = floor(jj);
	f = jj - z;
	
	if (z < 22991) {
		a = z;
	}else {
		aa = floor((z - 1867216.5) / 36524.25);
		a = z + 1 + aa - floor(aa / 4);
	}
	
	b = a + 1524;
	c = (b - 122.1) / 365.25;
	d = 365.25 * c;
	e = (b - d) / 30.6001;
	
	j = b - d - floor(30.6001 * e) + f;
	
	if (e < 13.5) {
		m = e - 1;	
	}else {
		m = e - 13;
	}
	
	if (m > 2.5){
		a = c - 4716;
	}else {
		a = c - 4715;
	}
	
	printf("cette 