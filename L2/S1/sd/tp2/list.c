#include "list.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>


struct node *new_node(item v) {
	struct node *res = malloc(sizeof(struct node));
	assign(res->value, v);
	res->next = NULL;
	return res;
}


void delete_node(struct node **m) {
	destroy((*m)->value);
	free(*m);
	*m = NULL;
}


list *new_list() {
	list * res = malloc(sizeof(list));
	res->first = NULL;
	res->length = 0;
	return res;
}


int is_empty(const list *l) {

	  if (l->length == 0) return 1;

	  return 0;
}


int list_length(const list *l) {
	  return l->length;
}


void add_node_list(list *l, struct node *m) {
	m->next = l->first;
	l->first = m;
	++l->length;
}

void print_list(const list *l) {

	struct node * m;

	for(m = l->first; m != NULL; m = m->next)
		display(m->value);

	printf("\n");

}


struct node * extract_node_list(list *l) {
	
	struct node * res = l->first;
 	
 	if (res != NULL) {
    		l->first = res->next;
  		--l->length;
    		res->next = NULL;
  	}
  	
  	return res;
}

void delete_list(list **l) {
	struct node *m;

	while ((*l)->length != 0) {
		m = extract_node_list(*l);
		delete_node(&m);
	}
	
	free(*l);
	*l = NULL;
}
