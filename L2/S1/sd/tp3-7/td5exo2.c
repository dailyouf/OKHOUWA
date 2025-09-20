#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>


int main() {

	return EXIT_SUCCESS;
}

link partition(link tree, int r) {
	
	if (tree == NULL) return NULL;

	if (r < size_binary_tree(tree->left) {
		partition(tree->left, r);
		rotate_right(tree);
	}	
	
		
	if (r > size_binary_tree(tree->left)){
		partition(tree->right, r-size_binary_tree(tree->left))
		rotate_left(tree);
	}
	
	return tree;

}


link insert_BST_rec(link tree, item x) {
	
	if (tree == NULL) return cons_binary_tree(x, NULL, NULL);
	
	if (less(x, get_binary_tree_root(tree))) {
		return insert_BST_rec(tree->left, x);
	}
			
	return insert_BST_rec(tree->right, x);
	
}

link insert_BST_iter(link tree, item x) {

	link tmp = tree, p;
	
	if (tree == NULL) tree = cons_binary_tree(x, NULL, NULL);
	
	while (tree != NULL) {
	
		p = tree;
		tree = (less(x, get_binary_tree_root(tree))) ? tree->left : tree->right;
	}
	
	if (less(x, get_binary_tree_root(p))) {
		p->left = cons_binary_tree(x, NULL, NULL);
	}
	
	else {
		p->right = cons_binary_tree(x, NULL, NULL);
	}
	
	return tmp;
}

link convertTabBST(item * tab, int n) {

	if (n == 0) return NULL;
	
	link tree = cons_binary_tree(tab[0], NULL, NULL);
	
	int i=0;
	
	for (i=1; i<n; i++) {
		
		insert_BST_iter(tree, tab[i]);	
		
	}

	return tree;
}

void addElem(link tree, item * tab) {
	tab[0] = get_binary_tree_root(tree);
	tab++;
}


void traverser_binary_tree_inorder2(link h, void (* add)(link, item *), item * tab) {
	
	if (h==NULL) return;
	
	traverser_binary_tree_inorder2(h->left, add, tab);
	add(h, tab);
	traverser_binary_tree_inorder2(h->right, add, tab);
	
}	


item * convertBSTTab(link tree) {
	
	if (is_empty_binary_tree(tree)) return NULL;

	item * tab = malloc(sizeof(item) * size_binary_tree(tree));
	
	
	// Correction du prof ....
	int i;
	
	for (i=0; i<size_binary_tree(tree); i++) {
		traverser_binary_tree_inorder2(tree, addElem, tab);
	}
	
	// Solution que je propose:	
	// traverser_binary_tree_inorder2(tree, addElem, tab);
	
	
	return tab;
	
	
}

