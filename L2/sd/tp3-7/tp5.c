#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 10

typedef struct {
	int n;
	char * tab;
} tas;


void init(char * tab, int n);

void afficher(char * tab, int n);

void fix_up_heap(char * tab, int i, int g);

void fix_down_heap(char * tab, int i, int d);

void heap_sort(char * tab, int g, int d);

int main(int argc, char ** argv) {

	int n = atoi(argv[1]);
	
	char * tab = malloc(sizeof(char) * n+1);
	
	init(tab, n);
	
	afficher(tab, n);
	
	heap_sort(tab, 1, n);
	
	afficher(tab, n);
	
	free(tab);
	tab = NULL;
	
	return EXIT_SUCCESS;

}

void init(char * tab, int n) {
	srand(time(NULL));
	int i;
	for(i=0; i<n; i++) {
		tab[i] = (rand() % 26) + 'A';
	}	
}

void afficher(char * tab, int n) {
	int i;
	printf("tab: { ");
	for(i=0; i<n+1; i++) {
		printf("%c ", tab[i]);
	}	
	printf("} \n");
}

void fix_up_heap(char * tab, int i, int g) {
	
	char tmp;
	
	while (i > g && tab[i] > tab[i / 2]) {
	
		tmp = tab[i];
		tab[i] = tab[i / 2];
		tab[i / 2] = tmp;

		i /= 2;
		
        }	
}


void fix_down_heap(char * tab, int i, int d) {

	while (2 * i <= d) {
		int j = 2 * i;
		if (j < d && tab[j] < tab[j + 1]) {
		    j++;
		}
		if (tab[i] >= tab[j]) {
		    break; 
		}
	
		char tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;

		i = j;
        }
}


void heap_sort(char * tab, int g, int d) {
	
	int k, tmp;
	
	for (k=g+1; k<d; k++) {
		fix_up_heap(tab, k, g);
	}
	
	
	while(g<d) {
		
		tmp = tab[d];
		tab[d] = tab[g];
		tab[g] = tmp;
		
		d--;
		
		fix_down_heap(tab, g, d);
		
	}
	
}
