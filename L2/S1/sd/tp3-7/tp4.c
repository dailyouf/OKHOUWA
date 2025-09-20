#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

link parse_subexp(char * chaine, int i);
link parse_expr(char * chaine);

int eval_tree(link tree);

void sub_tree_to_expr(link tree, char * chaine, int * i);
char * tree_to_expr(link tree);


int main(int argc, char ** argv) {
	
	
	link test = parse_expr(argv[1]);
	
	printf("résultat : %d \n", eval_tree(test));
	
	printf("arbre affiché : %s \n", tree_to_expr(test));
	
	delete_binary_tree(&test);
	
	return EXIT_SUCCESS;	
}


link parse_subexp(char * chaine, int i) {
	
	char c = chaine[i];
	
	link t =  cons_binary_tree(c, NULL, NULL);
		
	if (c=='+'|| c=='*') {
		t->left = parse_subexp(chaine, i+1);
		t->right = parse_subexp(chaine, i+1+size_binary_tree(t->left));
	}

	return	t;

}


link parse_expr(char * chaine) {

	return parse_subexp(chaine, 0);
}

int eval_tree(link tree) {
	
	int res = get_binary_tree_root(tree);
	
	if (res == '+') {
		return eval_tree(tree->left) + eval_tree(tree->right);
	}
	
	if (res == '*') {
		return eval_tree(tree->left) * eval_tree(tree->right);
	}
	
	return res - '0';
	
}


void sub_tree_to_expr(link tree, char * chaine, int * i) {
	
	if (tree == NULL)
		return;
	
	chaine[(*i)++] = get_binary_tree_root(tree);
	
	sub_tree_to_expr(tree->left, chaine, i);
	sub_tree_to_expr(tree->right, chaine, i);
	
}

char * tree_to_expr(link tree) {

	char * chaine = malloc(sizeof(char) * (size_binary_tree(tree) + 1));	
	
	int i=0;
	
	sub_tree_to_expr(tree, chaine, &i);
		
	chaine[i] = '\0';
	
	return chaine;

}
