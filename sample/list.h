#ifndef CLOCK_H
#define CLOCK_H
#include "setting.h"
#include <stdlib.h>

typedef MAN Keytype;

typedef struct List_node{
	Keytype data;
	struct List_node* next;
}LIST_NODE_SPACE, *LIST_NODE;

typedef struct List {
	int length;
	LIST_NODE head;
	LIST_NODE tail;
}LIST_SPACE, * LIST;

void List_init(LIST& list);

void List_insert(LIST list, Keytype key);

void List_delete(LIST list, int current_floor);

void List_show(LIST list);

#endif
