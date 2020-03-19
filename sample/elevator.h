#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "people.h"

OPERATION_STATUS Elevators_generate(ELEVATORS& elevators);

OPERATION_STATUS Elevators_init(PEOPLE& people, ELEVATORS& elevators, CLOCK& clock);

OPERATION_STATUS Elevators_free(PEOPLE people, ELEVATORS elevators, CLOCK clock);

ELEVATOR_STATUS Timt_flow(PEOPLE people, ELEVATORS elevators, CLOCK clock);

OPERATION_STATUS Event_flow(PEOPLE people, ELEVATORS elevators, CLOCK clock);

OPERATION_STATUS Man_leave(PEOPLE people, ELEVATOR elevator, int elevator_id);

OPERATION_STATUS Man_enter(PEOPLE people, ELEVATOR elevator, int elevator_id);

ELEVATOR_STATUS Elevator_move_judgment(ELEVATOR elevator);

void UI(PEOPLE people, ELEVATORS elevators, CLOCK clock);

void GUI();

OPERATION_STATUS Elevators_init_user(PEOPLE& people, ELEVATORS& elevators, CLOCK& clock, 
	int elevator_num, int floor_num, int capacity, int finished_time);

#endif
