#include "basis.h"

void gotoxy(int x, int y) {
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;
	// COORD cursorPosition = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void List_init(LIST& list)
{
	list = (LIST)malloc(sizeof(LIST_SPACE));
	if (!list)
	{
		error_message("List_init", ERROR_TYPE::MEMORY_INSUFFICIENT);
		return;
	}
	list->head = list->tail = NULL;
	list->length = 0;
	return;
}

void List_insert(LIST list, Keytype key)
{
	if (!list)
	{
		error_message("List_insert", ERROR_TYPE::NULL_PTR);
		return;
	}
	LIST_NODE inserted_node = (LIST_NODE)malloc(sizeof(LIST_NODE_SPACE));
	if (!inserted_node)
	{
		error_message("List_insert", ERROR_TYPE::MEMORY_INSUFFICIENT);
		return;
	}

	inserted_node->next = NULL;
	inserted_node->data = key;

	if (list->tail)
	{
		list->tail->next = inserted_node;
		list->tail = inserted_node;
	}
	else
		list->tail = list->head = inserted_node;

	list->length++;

	return;
}

void List_delete_node(LIST_NODE head, LIST_NODE deleted_node)
{
	LIST_NODE it;
	for (it = head; it->next != deleted_node; it = it->next);
	it->next = deleted_node->next;
	delete deleted_node->data;
	// 删除new的结构体
	free(deleted_node);

	return;
}

void List_show(LIST list)
{
	if (!list)
	{
		error_message("List_show", ERROR_TYPE::NULL_PTR);
		return;
	}
	printf("\n--\tlength of list: %d\t--\n", list->length);
	LIST_NODE it = list->head;
	//for (; it; it = it->next)
	//	printf("--\tnode: %d\t--\n", it->data);

	return;
}

int List_empty(LIST list)
{
	if (!list->length)
		return 1;
	return 0;
}

void List_free(LIST& list)
{
	if (!list)
		return ;
	while (list->length)
	{
		if (list->length == 1)
		{
			delete list->head->data;
			// 删除new的结构体
			free(list->head);
		}
		else
			List_delete_node(list->head, list->head->next);
		list->length--;
	}
	free(list);
	list = NULL;

	return ;
}

void Queue_init(QUEUE& queue)
{
	queue = (QUEUE)malloc(sizeof(QUEUE_SPACE));
	if (!queue)
	{
		error_message("Queue_init", ERROR_TYPE::MEMORY_INSUFFICIENT);
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
		error_message("Queue_push", ERROR_TYPE::NULL_PTR);
		return;
	}
	QUEUE_NODE inserted_node = (QUEUE_NODE)malloc(sizeof(QUEUE_NODE_SPACE));
	if (!inserted_node)
	{
		error_message("Queue_push", ERROR_TYPE::MEMORY_INSUFFICIENT);
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
		error_message("Queue_pop", ERROR_TYPE::NULL_PTR);
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
		error_message("Queue_front", ERROR_TYPE::NULL_PTR);
		return DEFAULT_KEY;
	}

	return queue->head->data;
}

void Queue_show(QUEUE queue)
{
	if (!queue)
	{
		error_message("Queue_show", ERROR_TYPE::NULL_PTR);
		return;
	}
	printf("\n--\tlength of queue: %d\t--\n", queue->length);
	QUEUE_NODE it = queue->head;
	//for (; it; it = it->next)
	//	printf("--\tnode: %d\t--\n", it->data);


	return;
}

int Queue_empty(QUEUE queue)
{
	if (!queue->length)
		return 1;
	return 0;
}

void Queue_free(QUEUE& queue)
{
	if (!queue)
		return ;
	while (queue->length)
		Queue_pop(queue);
	free(queue);
	queue = NULL;

	return ;
}

void error_message(string function_name, ERROR_TYPE error)
{
	string error_statement;
	switch (error)
	{
		case ERROR_TYPE::MEMORY_INSUFFICIENT: error_statement = "memory insufficient"; break;
		case ERROR_TYPE::NULL_PTR: error_statement = "null pointer"; break;
		case ERROR_TYPE::KEY_NOT_FOUND: error_statement = "key not found"; break;
		case ERROR_TYPE::STATUS_ERROR: error_statement = "status error"; break;
	default: error_statement = "Unknow";
	}
	cout << "\n--Error in " << function_name << ": " 
		 << error_statement << "--" << endl;
	return ;
}





