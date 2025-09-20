#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "binary_tree.h"

// Fonction pour afficher l'arbre en ordre croissant (parcours infixe)
void print_inorder(link tree) {
    if (tree == NULL) return;
    print_inorder(tree->left);
    printf("%d ", get_binary_tree_root(tree));
    print_inorder(tree->right);
}

int main() {
    // Initialisation de l'arbre BST
    link tree = NULL;

    // Insertion des valeurs dans le BST
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        tree = insert_BST(tree, values[i]);
    }

    // Afficher l'arbre avant suppression
    printf("Arbre BST avant suppression (ordre infixe) :\n");
    print_inorder(tree);
    printf("\n");

    // Supprimer un nœud spécifique
    int value_to_delete = 50;
    printf("Suppression du nœud avec la valeur : %d\n", value_to_delete);
    tree = delete_node_BST(tree, value_to_delete);

    // Afficher l'arbre après suppression
    printf("Arbre BST après suppression (ordre infixe) :\n");
    print_inorder(tree);
    printf("\n");

    // Libérer la mémoire de l'arbre
    delete_binary_tree(&tree);

    return 0;
}

