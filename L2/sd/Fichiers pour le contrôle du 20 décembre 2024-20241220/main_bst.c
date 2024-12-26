/** À COMPLÉTER AVEC LE NOM, LE PRÉNOM ET LE N° D'ÉTUDIANT(E) **/
/** DE CHAQUE ÉTUDIANT(E) AYANT TRAVAILLÉ SUR LE FICHIER **/
/* Etudiant(e) n°1, NOM : GHEDAMSI       Prénom : Youcef             N° : 12302243          */
/* Etudiant(e) n°1, NOM : HAMMADOU	 Prénom : Noussia            N° : 12308812      */

/** À COMPLÉTER AVEC LES BONNES INCLUSIONS DE FICHIERS **/
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include <time.h>

char* alloc_init_string_rand (int);
void usage_bst(char *);

int main(int argc, char **argv) {
	/** À COMPLÉTER AVEC LES DÉCLARATIONS DE VARIABLES LOCALES **/
	srand(time(NULL));

	int i, n, m;

	char * tab1, * tab2;
	
	link tree1, tree2, joined_tree;

	if (argc != 3) {
		printf("Nombre d'arguments erroné. Recommencez ! \n");
		usage_bst(argv[0]);
		return EXIT_FAILURE;
	}

	/** À COMPLÉTER AVEC LE CODE IMPLÉMENTANT CHACUNE DES ÉTAPES DU PROGRAMME DEMANDÉ **/
	
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	
	tab1 = alloc_init_string_rand(n);
	
	printf("tab1: { ");
	for(i=0; i<n-1; i++) {
		printf("%c, ", tab1[i]);
	}
	printf(" %c } \n", tab1[i]);
	
	
	tab2 = alloc_init_string_rand(m);
	
	printf("tab2: { ");
	for(i=0; i<m-1; i++) {
		printf("%c, ", tab2[i]);
	}
	printf(" %c } \n", tab2[i]);
	
	
	tree1 = cons_binary_tree(tab1[0], NULL, NULL);
	for(i=1; i<n; i++) {
		tree1 = insert_BST_it(tree1, tab1[i]);
	}
	
	printf("Arbre 1 avec insertion aux feuilles: \n");
	show_binary_tree(tree1, 0);
	
	tree2 = cons_binary_tree(tab2[0], NULL, NULL);
	for(i=1; i<m; i++) {
		tree2 = insert_BST_root(tree2, tab2[i]);
	}
	
	printf("Arbre 2 avec insertion à la racine: \n");
	show_binary_tree(tree2, 0);

	
	tree1 = delete_node_BST(tree1, select_BST(tree1, n/2)->label);
	
	printf("Arbre 1 après suppression du noeud de rang n/2: \n");
	show_binary_tree(tree1, 0);
	
	joined_tree = join_BST(tree1, tree2);
	
	printf("Affichage de l'arbre fusionné: ");
	traverse_inorder_it_BT(joined_tree, print_label);
	printf("\n");
	
	joined_tree = balance_BST(joined_tree);
	printf("Affichage de l'arbre fusionné: ");
	traverse_level_BT(joined_tree, print_label);
	printf("\n");
	
	delete_binary_tree(&joined_tree);
	
	free(tab1);
	tab1 = NULL;
	
	free(tab2);
	tab2 = NULL;

	return EXIT_SUCCESS;
}

/** Affiche le "format" de la ligne de commande en cas d'erreur */
void usage_bst(char *s) {
	printf("%s int int \n", s);
	printf("1er argument : taille du premier ABR\n");
	printf("2nd argument : taille du second ABR\n");

}

/** Initialise de manière pseudo-aléatoire une chaîne de caractères constituées */
/* de lettres majuscules de l'alphabet latin et renvoie la chaîne */
char * alloc_init_string_rand (int n) {
	int i;
	
	char * tab = malloc(sizeof(char) * n+1);
	
	for(i=0; i<n; i++) {
		tab[i] = (rand() % 26) + 'A';
	}
	
	return tab;
	
}
