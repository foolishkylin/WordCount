#ifndef PEOPLE_H
#define PEOPLE_H
#include "basis.h"
#include "clock.h"

OPERATION_STATUS People_set(PEOPLE& people, CLOCK clock);

OPERATION_STATUS Man_generate(PEOPLE people, ELEVATORS elevators, CLOCK clock);

OPERATION_STATUS Man_generate_judgment(PEOPLE people, ELEVATORS elevators, CLOCK clock);

OPERATION_STATUS Man_leave(PEOPLE people, CLOCK clock);

OPERATION_STATUS Queue_delete(QUEUE queue, int current_time);

OPERATION_STATUS Queue_delete_node(QUEUE_NODE head, QUEUE_NODE deleted_node, int current_time);

OPERATION_STATUS Man_generate(PEOPLE people, ELEVATORS elevators, CLOCK clock);

OPERATION_STATUS Man_push_in_button(MAN man, ELEVATOR elevator);

OPERATION_STATUS Man_push_leave_button(MAN man, ELEVATOR elevator);

#endif
