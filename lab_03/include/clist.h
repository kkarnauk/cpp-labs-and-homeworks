#pragma once

#define OFFSETOF(type, member) \
	(long)&(((type*)0)->member) \

#define CONTAINER_OF(ptr, type, member) (type*)((char*)(ptr) - OFFSETOF(type, member))

struct intrusive_list {
	struct intrusive_list* next;
	struct intrusive_list* prev;
};

void remove_node(struct intrusive_list* node);

void add_node(struct intrusive_list *where, struct intrusive_list* node);