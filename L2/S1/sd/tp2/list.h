#ifndef _LIST_H
#define _LIST_H

#include "item.h"

struct node {
	item value; /* value of node */
	struct node *next; /* pointer to next node */
};

typedef struct list {
 	 struct node *first; /* pointer to first node of list */
 	 int length; /* number of nodes in list */
}list;

/* allocates memory for one new node (with argument as value) and returns its address */
struct node *new_node(item);

/* frees memory allocated to node */
void delete_node(struct node **);

/* allocates memory for an empty list and returns its address */
list *new_list();

/* returns 1 if list is empty, returns 0 otherwise */
int is_empty(const list *);

/* returns number of nodes in list */
int list_length(const list *);

/* inserts node as first node of list */
void add_node_list(list *, struct node *);

/* prints all values of list */
void print_list(const list *);

/* extracts first node of list and returns its address */
struct node *extract_node_list(list *);

/* frees all memory allocated to list and to its nodes */
void delete_list(list **);

#endif
