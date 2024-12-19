#include <stdlib.h>
#include <stdio.h>

// Define the structure for a red-black tree node.
typedef struct RBTree {
        int label; // Label of the root
        struct RBTree* left; // Left subtree
        struct RBTree* right; // Right subtree
        int red; // Color: 1 if red, 0 if black
} * link;

// Function prototypes
link cons_tree_RB(int label, link left, link right, int red);
link insert_RB(link h, int value, int sw);
link insert(link root, int value);
link insert_RB_iter(link root, int value);
link rotate_left(link h);
link rotate_right(link h);
link partition_RB(link h, int k);
link join_RB(link h, link k);
link balance_RB(link h);
link delete_RB(link h, int value);
void print_tree(link root, int level);
link insert_root_recursive(link h, int value, int sw);
link insert_root(link root, int value);
link insert_root_iterative(link root, int value);
int height_RB(link h);
int size_RB(link h);


// Example usage
int main() {
        
       link root = NULL;
       root = cons_tree_RB(0, NULL, NULL, 0);
       
        root = insert(root, 10);
        root = insert(root, 20);
        root = insert(root, 15);
        root = insert_root(root, 25);

         // Affichage de l'arbre
        printf("Arbre Rouge-Noir:\n");
        print_tree(root, 0);
        
        
        return EXIT_SUCCESS;
}

// Create a new red-black tree node
link cons_tree_RB(int label, link left, link right, int red) {
        link new_node = malloc(sizeof(struct RBTree));
        new_node->label = label;
        new_node->left = left;
        new_node->right = right;
        new_node->red = red;
        return new_node;
}

// Perform a left rotation
link rotate_left(link h) {
        link x = h->right;
        h->right = x->left;
        x->left = h;
        x->red = h->red;
        h->red = 1;
        return x;
}

// Perform a right rotation
link rotate_right(link h) {
        link x = h->left;
        h->left = x->right;
        x->right = h;
        x->red = h->red;
        h->red = 1;
        return x;
}

// Fonction d'insertion récursive dans un arbre rouge-noir
link insert_RB(link h, int value, int sw) {
        if (h == NULL) // Si on atteint une feuille noire
                return cons_tree_RB(value, NULL, NULL, 1);

        // Cas où on rencontre un conflit rouge-rouge
        if (h->left && h->left->red && h->right && h->right->red) {
                h->red = 1;
                h->left->red = 0;
                h->right->red = 0;
        }

        if (value < h->label) {
                h->left = insert_RB(h->left, value, 0);
                if (h->red && h->left->red && sw) {
                        h = rotate_right(h);
                }
                if (h->left && h->left->red && h->left->left && h->left->left->red) {
                        h = rotate_right(h);
                        h->red = 0;
                        h->right->red = 1;
                }
        } else {
                h->right = insert_RB(h->right, value, 1);
                if (h->red && h->right->red && !sw) {
                        h = rotate_left(h);
                }
                if (h->right && h->right->red && h->right->right && h->right->right->red) {
                        h = rotate_left(h);
                        h->red = 0;
                        h->left->red = 1;
                }
        }

        return h;
}

// Fonction d'insertion dans l'arbre rouge-noir avec rétablissement de la couleur de la racine
link insert(link root, int value) {
        root = insert_RB(root, value, 0);
        root->red = 0; // La racine doit toujours être noire
        return root;
}


// Insert a new value into the red-black tree (iterative version)
link insert_RB_iter(link root, int value) {
        static link z = NULL;
        if (!z) z = cons_tree_RB(0, NULL, NULL, 0);

        link p = NULL, h = root;
        while (h != z) {
                p = h;
                if (value < h->label) {
                        h = h->left;
                } else {
                        h = h->right;
                }
        }

        link new_node = cons_tree_RB(value, z, z, 1);
        if (!p) {
                root = new_node;
        } else if (value < p->label) {
                p->left = new_node;
        } else {
                p->right = new_node;
        }

        // Fix the tree (coloring and rotations)
        // This part can be added to mirror the recursive version if required

        root->red = 0;
        return root;
}

// Partition the tree around the k-th element
link partition_RB(link h, int k) {
        if (!h) return NULL;

        int left_size = h->left ? h->left->red : 0;
        if (k < left_size) {
                h->left = partition_RB(h->left, k);
                h = rotate_right(h);
        } else if (k > left_size) {
                h->right = partition_RB(h->right, k - left_size - 1);
                h = rotate_left(h);
        }
        return h;
}

// Join two red-black trees
link join_RB(link h, link k) {
        if (!h) return k;
        if (!k) return h;

        h = partition_RB(h, h->red);
        h->right = k;
        h->red = 0;
        return h;
}

// Balance the red-black tree
link balance_RB(link h) {
        if (!h) return NULL;

        h = partition_RB(h, h->red / 2);
        h->left = balance_RB(h->left);
        h->right = balance_RB(h->right);
        return h;
}

// Delete a value from the red-black tree
link delete_RB(link h, int value) {
        if (!h) return NULL;

        if (value < h->label) {
                h->left = delete_RB(h->left, value);
        } else if (value > h->label) {
                h->right = delete_RB(h->right, value);
        } else {
                if (!h->left) {
                        link right = h->right;
                        free(h);
                        return right;
                }
                if (!h->right) {
                        link left = h->left;
                        free(h);
                        return left;
                }
                link min = h->right;
                while (min->left) min = min->left;
                h->label = min->label;
                h->right = delete_RB(h->right, min->label);
        }

        return h;
}



// Affiche l'arbre avec une indentation de 8 espaces
void print_tree(link root, int level) {
        if (root == NULL)
                return;

        // Augmenter le niveau de profondeur pour l'indentation
        level++;

        // Afficher d'abord le sous-arbre droit (pour afficher l'arbre "inversé" dans le terminal)
        print_tree(root->right, level);

        // Afficher le label du nœud avec l'indentation appropriée
        for (int i = 1; i < level; i++) {
                printf("        ");  // 8 espaces par niveau
        }
        printf("%d", root->label);
        if (root->red)
                printf(" (R)");  // Affiche (R) si le nœud est rouge
        else
                printf(" (B)");  // Affiche (B) si le nœud est noir
        printf("\n");

        // Afficher ensuite le sous-arbre gauche
        print_tree(root->left, level);
}


link insert_root_recursive(link h, int value, int sw) {
        // Si l'arbre est vide, créer un nouveau nœud rouge
        if (h == NULL) {
                return cons_tree_RB(value, NULL, NULL, 1);  // Nœud rouge
        }

        // Cas où on rencontre un conflit rouge-rouge
        if (h->left && h->left->red && h->right && h->right->red) {
                h->red = 1;
                h->left->red = 0;
                h->right->red = 0;
        }

        // Insertion récursive
        if (value < h->label) {
                h->left = insert_root_recursive(h->left, value, 0);
                if (h->red && h->left->red && sw) {
                        h = rotate_right(h);
                }
                if (h->left && h->left->red && h->left->left && h->left->left->red) {
                        h = rotate_right(h);
                        h->red = 0;
                        h->right->red = 1;
                }
        } else {
                h->right = insert_root_recursive(h->right, value, 1);
                if (h->red && h->right->red && !sw) {
                        h = rotate_left(h);
                }
                if (h->right && h->right->red && h->right->right && h->right->right->red) {
                        h = rotate_left(h);
                        h->red = 0;
                        h->left->red = 1;
                }
        }

        return h;
}

// Fonction pour insérer à la racine de manière récursive
link insert_root(link root, int value) {
        root = insert_root_recursive(root, value, 0);
        root->red = 0;  // La racine doit toujours être noire
        return root;
}


link insert_root_iterative(link root, int value) {
        static link z = NULL;
        if (!z) z = cons_tree_RB(0, NULL, NULL, 0);  // Créer une feuille noire fictive

        link p = NULL, h = root;
        
        // Trouver la position d'insertion de manière itérative
        while (h != z) {
                p = h;
                if (value < h->label) {
                        h = h->left;
                } else {
                        h = h->right;
                }
        }

        // Créer le nouveau nœud rouge à insérer
        link new_node = cons_tree_RB(value, z, z, 1);
        if (!p) {
                root = new_node;  // L'arbre était vide
        } else if (value < p->label) {
                p->left = new_node;
        } else {
                p->right = new_node;
        }

        // Corriger l'arbre pour respecter les propriétés rouges-noires
        // Effectuer les rotations nécessaires
        while (new_node != root && new_node->red && p->red) {
                if (new_node == p->left) {
                        p = rotate_right(p);
                } else {
                        p = rotate_left(p);
                }
        }

        root->red = 0;  // La racine doit toujours être noire
        return root;
}

int height_RB(link h) {
        if (h == NULL) {
                return 0;  // La hauteur d'un arbre vide est 0
        }

        // Calculer la hauteur pour les sous-arbres gauche et droit
        int left_height = height_RB(h->left);
        int right_height = height_RB(h->right);

        // La hauteur d'un nœud est le maximum des hauteurs de ses sous-arbres, 
        // plus 1 si ce n'est pas un nœud rouge
        if (h->red == 0) {  // Si le nœud est noir
                return (left_height > right_height ? left_height : right_height) + 1;
        } else {
                return (left_height > right_height ? left_height : right_height);
        }
}


int size_RB(link h) {
        if (h == NULL) {
                return 0;  // Si l'arbre est vide, la taille est 0
        }

        // Compter la taille des sous-arbres gauche et droit
        int left_size = size_RB(h->left);
        int right_size = size_RB(h->right);

        // Si le nœud est noir, il est comptabilisé dans la taille
        if (h->red == 0) {
                return left_size + right_size + 1;
        } else {
                return left_size + right_size;
        }
}



