#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "clist.h"

const int MAXLEN = 100;

struct point {
	int x, y;
	struct intrusive_list node;
};

struct point* new_point(int x, int y) {
	struct point* p = (struct point*)malloc(sizeof(struct point));
	p->x = x;
	p->y = y;
	p->node.next = NULL;
	p->node.prev = NULL;
	return p;
}

int size_of_list = 0;

void add_point(struct intrusive_list* where, int x, int y) {
	struct point* cur = new_point(x, y);
	add_node(where, &cur->node);
	size_of_list++;
}

void remove_point(struct intrusive_list* node, int x, int y) { 
	node = node->next;
	while (node != NULL) {
		struct point* p = CONTAINER_OF(node, struct point, node);
		struct intrusive_list* next_l = node->next;
		if (p->x == x && p->y == y) {
			remove_node(node);
			free(p);
			size_of_list--;
		}
		node = next_l;
	}
}

void show_all_points(const struct intrusive_list* node) {
	node = node->next;
	while (node != NULL) {
		const struct point* p = CONTAINER_OF(node, struct point, node);
		printf("(%d %d) ", p->x, p->y);
		node = node->next;
	}
	printf("\n");
}

void remove_all_points(struct intrusive_list* node) {
	node = node->next;
	while (node != NULL) {
		struct intrusive_list* next_l = node->next;
		remove_node(node);
		free(CONTAINER_OF(node, struct point, node));
		node = next_l;
		size_of_list--;
	}
}

struct point* start_work() {
	return new_point(0, 0);
}

void end_work(struct point* p) {
	remove_all_points(&p->node);
	free(p);
}

int main() {
	struct point* empt = start_work();
	while (true) {
		char s[MAXLEN + 1];
		fgets(s, MAXLEN, stdin);
		char *command = strtok(s, " ");
		if (strcmp(command, "add") == 0) {
			int x = atoi(strtok(NULL, " "));
			int y = atoi(strtok(NULL, " "));
			add_point(&empt->node, x, y);
		} else if (strcmp(command, "rm") == 0) {
			int x = atoi(strtok(NULL, " "));
			int y = atoi(strtok(NULL, " "));
			remove_point(&empt->node, x, y);
		} else if (strcmp(command, "print\n") == 0) {
			show_all_points(&empt->node);
		} else if (strcmp(command, "rma\n") == 0) {
			remove_all_points(&empt->node);
		} else if (strcmp(command, "len\n") == 0) {
			printf("%d\n", size_of_list);
		} else if (strcmp(command, "exit\n") == 0) {
			break;
		} else {
			printf("Unknown command\n");
		}
	}
	end_work(empt);
	return 0;
}