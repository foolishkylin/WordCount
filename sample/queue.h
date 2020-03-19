#ifndef CLOCK_H
#define CLOCK_H
#include "setting.h"

typedef MAN Keytype;

const Keytype DEFAULT_KEY = NULL;

typedef struct Queue_node {
	Keytype data;
	struct Queue_node* next;
}QUEUE_NODE_SPACE, *QUEUE_NODE;

typedef struct Queue {
	QUEUE_NODE head;
	QUEUE_NODE tail;
	int length;
}QUEUE_SPACE, *QUEUE;

void Queue_init(QUEUE& queue);

void Queue_push(QUEUE queue, Keytype key);

void Queue_pop(QUEUE queue);

Keytype Queue_front(QUEUE queue);

void Queue_show(QUEUE queue);

#endif
