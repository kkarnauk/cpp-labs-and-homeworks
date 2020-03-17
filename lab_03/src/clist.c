#include <stdlib.h>
#include <stddef.h>
#include "clist.h"

void remove_node(struct intrusive_list* node) {
	if (node->next != NULL && node->prev != NULL) {
		node->next->prev = node->prev;
		node->prev->next = node->next;
	} else if (node->next != NULL) {
		node->next->prev = NULL;
	} else if (node->prev != NULL) {
		node->prev->next = NULL;
	}
}

void add_node(struct intrusive_list* where, struct intrusive_list* node) {
	if (where->next != NULL) {
		node->next = where->next;
		where->next->prev = node;
	}
	where->next = node;
	node->prev = where;
} 

struct intrusive_list* new_list() {
	return (struct intrusive_list*)malloc(sizeof(struct intrusive_list));
}