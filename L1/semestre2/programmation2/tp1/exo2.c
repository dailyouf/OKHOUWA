#include<stdlib.h>
#include<stdio.h>

char motif_carre_NO_SE(int i, int j, int n);
char motif_carre_SE_NO(int i, int j, int n);


int main(){
	
	int i, j;
	unsigned n;
	
	scanf("%u", &n);
	
	for (i=0; i<n; i++){
	
		for (j=0; j<n; j++){
			
			if (i < n / 2){
				printf("%c ", motif_carre_NO_SE(i, j, n));
			}else {
				printf("%c ", motif_carre_SE_NO(i, j, n));
			}

		}
		printf("\n");
	}
		
	
	
	return EXIT_SUCCESS;

}

char motif_carre_NO_SE(int i, int j, int n){
	
	if (j < (n/2)) {
		if (i==0 || j==0 || i==(n/2)-1 || j==(n/2)-1){
			return '*';
		}else {
			return ' ';
		}	
	}else{	
		j -= n/2;
		if (i % 2 == 0){
			if (j % 2 == 0){
				return 'o';
			}else {
				return '+';
			}
		}else {
			if (j % 2 == 0){
				return '+';
			}else {
				return 'o';
			}
		}
	}
		
}

char motif_carre_SE_NO(int i, int j, int n){

	i -= n / 2;
	
	
	if (j < (n/2)) {
		j += n / 2;
		
	}else{	
	
		j -= n / 2;	
	}		
	return motif_carre_NO_SE(i, j, n);
	
}
