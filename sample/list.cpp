#include "list.h"

void List_init(LIST& list)
{
	list = (LIST)malloc(sizeof(LIST_SPACE));
	if (!list)
	{
		error_message("List_init", MEMORY_INSUFFICIENT);
		return;
	}
	list->head = list->tail = NULL;
	list->length = 0;
	return ;
}

void List_insert(LIST list, Keytype key)
{
	if (!list)
	{
		error_message("List_insert", NULL_PTR);
		return ;
	}
	LIST_NODE inserted_node = (LIST_NODE)malloc(sizeof(LIST_NODE_SPACE));
	if (!inserted_node)
	{
		error_message("List_insert", MEMORY_INSUFFICIENT);
		return ;
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

	return ;
}

void List_delete_node(LIST_NODE head, LIST_NODE deleted_node)
{
	LIST_NODE it;
	for (it = head; it->next != deleted_node; it = it->next);
	it->next = deleted_node->next;
	free(deleted_node);

	return ;
}

void List_delete(LIST list, int current_floor)
{
	if (!list || !list->length)
	{
		error_message("List_delete", NULL_PTR);
		return;
	}
	bool not_deleted = TRUE;
	for (LIST_NODE it = list->head; it && not_deleted; )
		if (it->data->out_floor == current_floor) // it->data->out_floor = current_floor
		{
			not_deleted = FALSE;
			if (list->length == 1)
			{
				free(list->head);
				list->head = list->tail = NULL;
			}
			else if (it == list->head)
			{
				list->head = list->head->next;
				free(it);
			}
			else
			{
				if (it == list->tail)
				{
					LIST_NODE new_tail;
					for (new_tail = list->head; new_tail->next!= list->tail; new_tail = new_tail->next);
					list->tail = new_tail;
				}
				List_delete_node(list->head, it);
			}
			list->length--;
		}
		else
			it = it->next;
	if (not_deleted)
		error_message("List_delete", KEY_NOT_FOUND);
	return ;
}

void List_show(LIST list)
{
	if (!list)
	{
		error_message("List_show", NULL_PTR);
		return;
	}
	printf("\n--\tlength of list: %d\t--\n", list->length);
	LIST_NODE it = list->head;
	//for (; it; it = it->next)
	//	printf("--\tnode: %d\t--\n", it->data);

	return;
}
