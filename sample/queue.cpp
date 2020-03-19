#include "queue.h"

void Queue_init(QUEUE& queue)
{
	queue = (QUEUE)malloc(sizeof(QUEUE_SPACE));
	if (!queue)
	{
		error_message("Queue_init", MEMORY_INSUFFICIENT);
		return;
	}
	queue->head = queue->tail = NULL;
	queue->length = 0;
	return;
}

void Queue_push(QUEUE queue, Keytype key)
{
	if (!queue)
	{
		error_message("Queue_push", NULL_PTR);
		return;
	}
	QUEUE_NODE inserted_node = (QUEUE_NODE)malloc(sizeof(QUEUE_NODE_SPACE));
	if (!inserted_node)
	{
		error_message("Queue_push", MEMORY_INSUFFICIENT);
		return;
	}

	inserted_node->next = NULL;
	inserted_node->data = key;
	if (queue->tail)
	{
		queue->tail->next = inserted_node;
		queue->tail = inserted_node;
	}
	else
		queue->tail = queue->head = inserted_node;

	queue->length++;

	return;
}

void Queue_pop(QUEUE queue)
{
	if (!queue || !queue->length)
	{
		error_message("Queue_pop", NULL_PTR);
		return;
	}
	QUEUE_NODE front = queue->head;
	if (queue->length == 1)
		queue->head = queue->tail = NULL;
	else
	{
		queue->head = queue->head->next;
	}
	free(front);
	queue->length--;

	return;
}

Keytype Queue_front(QUEUE queue)
{
	if (!queue || !queue->length)
	{
		error_message("Queue_front", NULL_PTR);
		return DEFAULT_KEY;
	}
	
	return queue->head->data;
}

void Queue_show(QUEUE queue)
{
	if (!queue)
	{
		error_message("Queue_show", NULL_PTR);
		return;
	}
	printf("\n--\tlength of queue: %d\t--\n", queue->length);
	QUEUE_NODE it = queue->head;
	//for (; it; it = it->next)
	//	printf("--\tnode: %d\t--\n", it->data);


	return;
}