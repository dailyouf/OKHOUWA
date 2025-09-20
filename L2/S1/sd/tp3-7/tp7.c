#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bst.h"

#define MAX 10

void init(char * tab, int n);

void afficher(char * tab, int n);


int main(int argc, char ** argv) {

	int i, n = atoi(argv[1]);
	
	char * tab = malloc(sizeof(char) * n+1);
	
	link tree;
	
	init(tab, n);
	
	afficher(tab, n);
	
	tree = cons_binary_tree(tab[0], NULL, NULL);
	for(i=1; i<n; i++) {
		tree = insert_BST(tree, tab[i]);
	}
	
	printf("tab trié: { ");
	traverse_inorder_binary_tree(tree, print_label);
	
	printf("\n");
	
	delete_binary_tree(&tree);
	
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
