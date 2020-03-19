#include "people.h"

OPERATION_STATUS Man_push_in_button(MAN man, ELEVATOR elevator)
{
	if (man->in_floor == elevator->current_floor)
		// 当前层有人来，则默认按下呼叫上升
		elevator->call_up[man->in_floor] = TRUE;
	else if (man->in_floor > elevator->current_floor)
		elevator->call_up[man->in_floor] = TRUE;
	else
		elevator->call_down[man->in_floor] = TRUE;
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Man_push_leave_button(MAN man, ELEVATOR elevator)
{
	if (man->out_floor == elevator->current_floor)
	{
		elevator->call_up[man->out_floor] = TRUE;
		// TODO
	}
	else if (man->out_floor > elevator->current_floor)
		elevator->call_out[man->out_floor] = TRUE;
	else
		elevator->call_out[man->out_floor] = TRUE;
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS People_set(PEOPLE& people, CLOCK clock)
{
	people = (PEOPLE)malloc(sizeof(PEOPLE_SPACE));
	if (people)
	{
		int it;
		for (it = 0; it < ELEVATOR_NUM; it++)
			List_init(people->elevator_list[it]);
		for (it = 0; it < FLOOR_NUM; it++)
			for (int nit = 0; nit < ELEVATOR_NUM; nit++)
				Queue_init(people->waiting_queue[it][nit]);
		people->inter_time = 0;

		return OPERATION_STATUS::SUCCESS;
	}
	return OPERATION_STATUS::FAIL;
}

OPERATION_STATUS Man_generate(PEOPLE people, ELEVATORS elevators, CLOCK clock)
{
	MAN new_man = new MAN_SPACE;
	ELEVATOR elevator = elevators->elevator[0];
	int min_num = 9999, it;
	if (new_man)
	{
		new_man->in_floor = rand() % elevator->floor_num;
		new_man->out_floor = rand() % elevator->floor_num;
		if (new_man->in_floor == new_man->out_floor)
			new_man->out_floor = (new_man->out_floor + 1) % elevator->floor_num;
		new_man->give_up_time = clock->current_time + rand() % TIME_BLOCK + TIME_BLOCK * 4;
		new_man->name = ((clock->current_time % 2) ? "靓仔" : "靓女") + to_string(new_man->give_up_time);
		people->inter_time = clock->current_time + rand() % TIME_BLOCK;

		QUEUE queue = people->waiting_queue[new_man->in_floor][0];
		// 来到等待队列最短的电梯面前
		for (it = 0; it < elevators->elevator_num; it++)
			if (min_num > people->waiting_queue[new_man->in_floor][it]->length)
			{
				min_num = people->waiting_queue[new_man->in_floor][it]->length;
				queue = people->waiting_queue[new_man->in_floor][it];
				elevator = elevators->elevator[it];
			}
		Queue_push(queue, new_man);
		Man_push_in_button(new_man, elevator);

		return OPERATION_STATUS::SUCCESS;
	}
	return OPERATION_STATUS::FAIL;
}

OPERATION_STATUS Man_generate_judgment(PEOPLE people, ELEVATORS elevators, CLOCK clock)
{
	if (clock->current_time >= people->inter_time)
		Man_generate(people, elevators, clock);
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Man_leave(PEOPLE people, CLOCK clock)
{
	for (int i = 0; i < people->floor_num; i++)
		for (int j = 0; j < people->elevator_num; j++)
		Queue_delete(people->waiting_queue[i][j], clock->current_time);
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Queue_delete_node(QUEUE_NODE head, QUEUE_NODE deleted_node, int current_time)
{
	QUEUE_NODE it;
	for (it = head; it->next != deleted_node; it = it->next);
	it->next = deleted_node->next;
	//cout << "> (" << current_time << "t) 此时" << deleted_node->data->in_floor << "层的" << deleted_node->data->name
	//	<< "心里急燥，克制不住，终于离开了电梯" << endl;
	delete deleted_node->data;
	// 删除new的结构体
	free(deleted_node);

	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Queue_delete(QUEUE queue, int current_time)
{
	if (!queue || !queue->length)
		return OPERATION_STATUS::SUCCESS;
	bool not_deleted = TRUE;
	QUEUE_NODE it = queue->head;
	while (it)
		if (current_time >= it->data->give_up_time)
		{
			not_deleted = FALSE;
			if (queue->length == 1)
			{
				//cout << "> (" << current_time << "t) 此时" << queue->head->data->in_floor << "层的" << queue->head->data->name
				//	<< "心里急燥，克制不住，终于离开了电梯" << endl;
				free(queue->head);
				queue->head = queue->tail = NULL;
				it = NULL;
			}
			else if (it == queue->head)
			{
				//cout << "> (" << current_time << "t) 此时" << queue->head->data->in_floor << "层的" << queue->head->data->name
				//	<< "心里急燥，克制不住，终于离开了电梯" << endl;
				queue->head = queue->head->next;
				free(it);
				it = queue->head;
			}
			else
			{
				if (it == queue->tail)
				{
					
					//cout << "> (" << current_time << "t) 此时" << queue->tail->data->in_floor << "层的" << queue->tail->data->name
					//	<< "心里急燥，克制不住，终于离开了电梯" << endl;
					QUEUE_NODE new_tail;
					for (new_tail = queue->head; new_tail->next != queue->tail; new_tail = new_tail->next);
					queue->tail = new_tail;
					Queue_delete_node(queue->head, it, current_time);
					it = NULL;
				}
				else
				{
					QUEUE_NODE nit = it->next;
					Queue_delete_node(queue->head, it, current_time);
					it = nit;
				}
			}
			queue->length--;
		}
		else
			it = it->next;
	//if (not_deleted)
	//	error_message("List_delete", KEY_NOT_FOUND);
	return OPERATION_STATUS::SUCCESS;
}

