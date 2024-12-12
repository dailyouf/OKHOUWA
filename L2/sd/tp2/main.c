#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <time.h>

struct compteur {
	int cmp;
	int afect;
};


struct compteur * tri_bulles(list * l);


int main(int argc, char ** argv) {
	
	srand(time(NULL));

	int i, taille;
	
	list * l = new_list();
	
	struct node * n;
	
	struct compteur * cpt;


	printf("Veuillez entrer en arguments la taille de la liste suivi des élements eventuels de la liste \n");

	if (argc == 1) {
		printf("Pas assez d'arguments \n");
		exit(1);	
	}
	
	taille = atoi(argv[1]);
	
	if (argc == 2) {
		for (i=0; i<taille; i++) {
		
			n = new_node( (float) rand() / RAND_MAX * 100.00);
		
			add_node_list(l, n);
		}
		
	}
	
	else {
		
		if (taille != argc - 2) {
			printf("Erreur taille du tableau \n");
			exit(1);	
		}
		
		for (i=0; i<taille; i++) {
		
			n = new_node(atof(argv[i + 2]));
			
			add_node_list(l, n);
		}	
	}
	
	
	printf("Liste initiale: ");	
	print_list(l);
	
	cpt = tri_bulles(l);
	
	printf("Liste triée après %d comparaisons et %d affectation: ", cpt->cmp, cpt->afect);
	print_list(l);
	
	
}

struct compteur * tri_selection(list * l, int taille) {
	
	int i;
	
	struct node * min, *q, * f = l->first;
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->cmp = 0;
	cpt->afect = 0;
	
	while (f->next != NULL) {
		
		min = f;
		q = f->next;
		
		while (q != NULL) {
			
			if (min->value > q->value) {
				min = q;
			}
		
			q = q->next;
		}
		
					
		if (min != f) 
			exch(min, f); 
		
		f = f->next;
		
	}
	
	return cpt;

}

struct node *find_min(struct node *start, struct compteur *cpt) {
        struct node *min = start;
        struct node *q = start->next;
        
        while (q != NULL) {
                cpt->cmp++;
                if (q->value < min->value) {
                        min = q;
                }
                q = q->next;
        }
        return min;
}

void selection_sort_recursive(struct node *start, struct compteur *cpt) {
        if (start == NULL || start->next == NULL) {
                return;
        }
        
        struct node *min = find_min(start, cpt);
        
        if (min != start) {
                exchange(min, start); // Échange la valeur des nœuds
                cpt->afect += 3; // Compte les affectations
        }
        
        selection_sort_recursive(start->next, cpt);
}

struct compteur *tri_selection(list *l, int taille) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->cmp = 0;
        cpt->afect = 0;
        
        selection_sort_recursive(l->first, cpt);
        
        return cpt;
}


/* Tri par insertion non récursif pour liste chaînée */
void insertion_sort(list *lst) {
        list *sorted_list = new_list(); /* Liste triée vide */
        struct node *current = lst->first;
        
        while (current != NULL) {
                struct node *next = current->next; /* Sauvegarde du prochain élément */
                current->next = NULL; /* Déconnexion du noeud */
                sorted_insert(sorted_list, current);
                current = next;
        }
        lst->first = sorted_list->first;
        lst->length = sorted_list->length;
        delete_list(&sorted_list); /* Libère la mémoire de la liste temporaire */
}


/* Fonction récursive pour insérer un noeud dans une liste triée */
struct node *sorted_insert_recursive(struct node *sorted_list, struct node *new_node) {
        if (sorted_list == NULL || sorted_list->value >= new_node->value) {
                new_node->next = sorted_list;
                return new_node;
        } else {
                sorted_list->next = sorted_insert_recursive(sorted_list->next, new_node);
                return sorted_list;
        }
}

/* Fonction récursive pour trier la liste par insertion */
struct node *insertion_sort_recursive(struct node *head) {
        if (head == NULL || head->next == NULL) {
                return head;
        }
        
        struct node *sorted_list = insertion_sort_recursive(head->next);
        head->next = NULL;
        return sorted_insert_recursive(sorted_list, head);
}

/* Appelle la version récursive pour trier toute la liste */
void insertion_sort_rec(list *lst) {
        lst->first = insertion_sort_recursive(lst->first);
}


struct compteur * tri_bulles(list * l) {
	
	int i = 1;
	
	struct node * p, *q;
	
	struct compteur * cpt = malloc(sizeof(struct compteur));
	
	cpt->cmp = 0;
	cpt->afect = 0;
	
	
	while (i != 0){
		
		i=0;
				
		p = l->first;
		q = l->first->next;
		
		cpt->afect += 2;
		
		while (q != NULL) {
			
			cpt->cmp++;
			
			if ( p->value > q->value) {
				
				exch(p->value, q->value);
				
				cpt->afect += 3;
				
				i=1;
			
			}
			
			p = p->next;
			q = q->next;
			
			cpt->afect += 2;
			
		}
		
		
	}
	
	return cpt;

}

int bubble_pass(struct node *start, struct compteur *cpt) {
        int swapped = 0;
        struct node *p = start;
        struct node *q = start->next;
        
        while (q != NULL) {
                cpt->cmp++;
                
                if (p->value > q->value) {
                        exchange(p->value, q->value); // Échange les valeurs
                        cpt->afect += 3; // Compte les affectations
                        swapped = 1;
                }
                
                p = p->next;
                q = q->next;
                cpt->afect += 2; // Compte les déplacements de pointeurs
        }
        
        return swapped;
}

void bubble_sort_recursive(struct node *start, struct compteur *cpt) {
        if (start == NULL || start->next == NULL) {
                return;
        }
        
        if (bubble_pass(start, cpt)) {
                bubble_sort_recursive(start, cpt); // Recommence si des échanges ont eu lieu
        }
}

struct compteur *tri_bulles(list *l) {
        struct compteur *cpt = malloc(sizeof(struct compteur));
        cpt->cmp = 0;
        cpt->afect = 0;
        
        bubble_sort_recursive(l->first, cpt);
        
        return cpt;
}


#include "list.h"

// Fonction qui divise la liste en deux
void split_list(list *source, list **front_ref, list **back_ref) {
        struct node *fast;
        struct node *slow;
        slow = source->first;
        fast = source->first->next;

        // Avance de deux pas pour fast, un pas pour slow
        while (fast != NULL) {
                fast = fast->next;
                if (fast != NULL) {
                        slow = slow->next;
                        fast = fast->next;
                }
        }

        // slow est à la fin de la première moitié
        *front_ref = new_list();
        *back_ref = new_list();
        (*front_ref)->first = source->first;
        (*back_ref)->first = slow->next;
        slow->next = NULL;
}

// Fusionne deux sous-listes triées
struct node* sorted_merge(struct node* a, struct node* b) {
        struct node* result = NULL;

        if (a == NULL) 
                return b;
        if (b == NULL)
                return a;

        if (a->value <= b->value) {
                result = a;
                result->next = sorted_merge(a->next, b);
        } else {
                result = b;
                result->next = sorted_merge(a, b->next);
        }
        return result;
}

// Fonction récursive de tri par fusion
void merge_sort(list **lst_ref) {
        struct node *head = (*lst_ref)->first;
        list *a, *b;

        // Cas de base : si la liste est vide ou a un seul élément
        if ((head == NULL) || (head->next == NULL)) {
                return;
        }

        // Diviser la liste en deux moitiés
        split_list(*lst_ref, &a, &b);

        // Tri récursif sur chaque moitié
        merge_sort(&a);
        merge_sort(&b);

        // Fusionner les deux moitiés triées
        (*lst_ref)->first = sorted_merge(a->first, b->first);
}


#include "list.h"

// Fusionne deux sous-listes
struct node* sorted_merge(struct node* a, struct node* b) {
        struct node dummy;
        struct node* tail = &dummy;
        dummy.next = NULL;

        while (1) {
                if (a == NULL) {
                        tail->next = b;
                        break;
                }
                if (b == NULL) {
                        tail->next = a;
                        break;
                }

                if (a->value <= b->value) {
                        tail->next = a;
                        a = a->next;
                } else {
                        tail->next = b;
                        b = b->next;
                }
                tail = tail->next;
        }
        return dummy.next;
}

// Tri par fusion non récursif
void merge_sort_non_recursive(list *lst) {
        int width, n;
        struct node *p, *q, *e, *tail;
        struct node *list_head = lst->first;

        if (!list_head || !list_head->next)
                return;

        n = lst->length;
        for (width = 1; width < n; width *= 2) {
                struct node dummy;
                dummy.next = list_head;
                tail = &dummy;

                while (list_head) {
                        p = list_head;
                        q = split(p, width);
                        list_head = split(q, width);
                        e = sorted_merge(p, q);
                        while (e) {
                                tail->next = e;
                                tail = e;
                                e = e->next;
                        }
                }
                list_head = dummy.next;
        }
        lst->first = list_head;
}


#include "list.h"

// Partitionne la liste autour d'un pivot
struct node *partition(struct node *head, struct node **front, struct node **back) {
        struct node *pivot = head;
        struct node *cur = head->next;

        *front = new_list();
        *back = new_list();

        while (cur != NULL) {
                struct node *next = cur->next;
                if (cur->value < pivot->value) {
                        cur->next = (*front)->first;
                        (*front)->first = cur;
                } else {
                        cur->next = (*back)->first;
                        (*back)->first = cur;
                }
                cur = next;
        }

        return pivot;
}

// Fonction récursive de tri rapide
void quick_sort(list **lst_ref) {
        struct node *head = (*lst_ref)->first;
        list *front, *back;

        if (head == NULL || head->next == NULL) {
                return;
        }

        // Partitionner la liste
        struct node *pivot = partition(head, &front, &back);

        // Tri récursif
        quick_sort(&front);
        quick_sort(&back);

        // Reconstruire la liste avec pivot au milieu
        if (front != NULL) {
                (*lst_ref)->first = front->first;
                struct node *temp = front->first;
                while (temp->next != NULL) {
                        temp = temp->next;
                }
                temp->next = pivot;
        } else {
                (*lst_ref)->first = pivot;
        }
        pivot->next = back->first;
}


#include "list.h"
#include <stack>

// Fonction de partition pour Quick Sort non récursif
struct node* partition_non_recursive(struct node* head, struct node** front, struct node** back) {
        struct node* pivot = head;
        struct node* current = head->next;

        *front = new_list();
        *back = new_list();

        while (current) {
                struct node* next = current->next;
                if (current->value < pivot->value) {
                        current->next = (*front)->first;
                        (*front)->first = current;
                } else {
                        current->next = (*back)->first;
                        (*back)->first = current;
                }
                current = next;
        }
        return pivot;
}

// Tri rapide non récursif
void quick_sort_non_recursive(list* lst) {
        if (!lst || lst->first == NULL) return;

        std::stack<list*> stack;
        stack.push(lst);

        while (!stack.empty()) {
                list *curr = stack.top();
                stack.pop();

                if (curr->first == NULL || curr->first->next == NULL) continue;

                list *front, *back;
                struct node *pivot = partition_non_recursive(curr->first, &front, &back);

                if (front && front->first) stack.push(front);
                if (back && back->first) stack.push(back);

                if (front) {
                        curr->first = front->first;
                        struct node *temp = front->first;
                        while (temp->next != NULL) temp = temp->next;
                        temp->next = pivot;
                } else {
                        curr->first = pivot;
                }
                pivot->next = back ? back->first : NULL;
        }
}






struct node **list_to_array(list *l) {
        int taille = size_of_list(l);  // Obtenir la taille de la liste
        struct node **array = malloc(taille * sizeof(struct node*));  // Créer un tableau de pointeurs vers des nodes

        struct node *current = l->first;
        int i = 0;

        while (current != NULL) {
                array[i] = current;  // Ajouter chaque élément de la liste au tableau
                current = current->next;
                i++;
        }

        return array;  // Retourne le tableau de nodes
}



void array_to_list(list *l, struct node **array) {
        l->first = NULL;  // Réinitialiser la liste

        for (int i = 0; i < size_of_list(l); i++) {
                struct node *n = array[i];
                n->next = NULL;  // Assurez-vous que le pointeur `next` est NULL avant d'ajouter à la liste
                add_node_list(l, n);  // Ajouter chaque élément du tableau à la liste
        }
}



#include "list.h"

/* Fonction pour obtenir le nœud à une position spécifique */
struct node *get_node_at(list *lst, int index) {
        struct node *current = lst->first;
        for (int i = 0; i < index && current != NULL; i++) {
                current = current->next;
        }
        return current;
}

/* Tri Shell non récursif */
void shell_sort_non_recursive(list *lst) {
        int gap, i, j;
        struct node *node_i, *node_j;
        item temp;

        int n = list_length(lst);

        for (gap = n / 2; gap > 0; gap /= 2) {
                for (i = gap; i < n; i++) {
                        node_i = get_node_at(lst, i);
                        temp = node_i->value;

                        j = i;
                        while (j >= gap) {
                                node_j = get_node_at(lst, j - gap);
                                if (node_j->value <= temp) {
                                        break;
                                }

                                /* décalage des éléments */
                                get_node_at(lst, j)->value = node_j->value;
                                j -= gap;
                        }

                        /* Insertion de l'élément à la bonne position */
                        get_node_at(lst, j)->value = temp;
                }
        }
}


#include "list.h"

/* Fonction pour obtenir le nœud à une position spécifique */
struct node *get_node_at(list *lst, int index) {
        struct node *current = lst->first;
        for (int i = 0; i < index && current != NULL; i++) {
                current = current->next;
        }
        return current;
}

/* Fonction récursive pour le tri Shell */
void shell_sort_recursive_helper(list *lst, int n, int gap) {
        if (gap == 0) {
                return;
        }

        int i, j;
        struct node *node_i, *node_j;
        item temp;

        for (i = gap; i < n; i++) {
                node_i = get_node_at(lst, i);
                temp = node_i->value;

                j = i;
                while (j >= gap) {
                        node_j = get_node_at(lst, j - gap);
                        if (node_j->value <= temp) {
                                break;
                        }

                        /* décalage des éléments */
                        get_node_at(lst, j)->value = node_j->value;
                        j -= gap;
                }

                /* Insertion de l'élément à la bonne position */
                get_node_at(lst, j)->value = temp;
        }

        /* Appel récursif avec un gap réduit */
        shell_sort_recursive_helper(lst, n, gap / 3);
}

/* Fonction principale pour le tri Shell récursif */
void shell_sort_recursive(list *lst) {
	int h = 1;
        while (h < list_length(lst) / 3) {
                h = 3 * h + 1;
        }
        shell_sort_recursive_helper(lst, list_length(lst), h / 3);
}






