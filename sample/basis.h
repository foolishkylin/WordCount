#ifndef BASIS_H
#define BASIS_H
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <list>
#include <string>
using namespace std;

const int GATE_CLOSE_TEST = 20;
const int GATE_ACTIVITY_TIME = 10;
const int SINGLE_MAN_ACTIVITY = 10;
const int IDLE_TEST = 15;
const int SINGLE_FLOOR_UP = 5;
const int SINGLE_FLOOR_DOWN = 10;

const int TIMESCALE = 100;
const int TIME_BLOCK = 20;
const int FINISHED_TIME_UNIT = 5000;

const int FLOOR_NUM = 8;
const int ELEVATOR_NUM = 3;
const int ELEVATOR_CAPACITY = 5;
const int FINISHED_TIME = 500;
const int DEFAULT_FLOOR = 1; 

enum class EVENT_ {
	UNTIME,
	UP,
	DOWN,
	IDLE_TEST,
	GATE_OPENING,
	GATE_CLOSING,
	STANDBY,
	PEOPLE_FLOW
};

enum class ERROR_TYPE {
	MEMORY_INSUFFICIENT,
	NULL_PTR,
	KEY_NOT_FOUND,
	STATUS_ERROR
};

enum class ELEVATOR_STATUS {
	OPERATING,
	UP,
	DOWN,
	IDLE,
	IDLE_MOVING,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_TEST,
	STANDBY,
	CUTOFF,
	DEFAULT
};

enum class GATE_STATUS {
	OPENING,
	OPENED,
	CLOSING,
	CLOSED
};

enum class OPERATION_STATUS {
	SUCCESS,
	FAIL,
	END
};

enum class EVENT {
	TIMED_ELEVATOR_UP,
	TIMED_ELEVATOR_DOWN,
	TIMED_OPEN_DOOR,
	TIMED_PEOPLE_COME,
	TIMED_PEOPLE_LEAVE,
	TIMED_CLOSE_DOOR_TEST,
	TIMED_CLOSE_DOOR,
	TIMED_IDLE_TEST,
	TIMED_IDLE,
	UNTIMED_ELEVATOR_MOVE_JUDGE,
	UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE,
	UNTIMED_PEOPLE_FLOW_JUDGE
};

typedef struct {
	int current_time;
	int finish_time;
} CLOCK_SPACE, *CLOCK;

typedef struct {
	ELEVATOR_STATUS status;
	GATE_STATUS gate_status;
	EVENT event;
	string statement;
	bool call_up[FLOOR_NUM];
	bool call_down[FLOOR_NUM];
	bool call_out[FLOOR_NUM]; 
	int capacity = ELEVATOR_CAPACITY;
	int current_floor;
	int floor_num;
	int timer;
	bool people_flow;
} ELEVATOR_SPACE, * ELEVATOR;

typedef struct {
	ELEVATOR elevator[ELEVATOR_NUM];
	int elevator_num;
} ELEVATORS_SPACE, *ELEVATORS;

typedef struct {
	int in_floor = 0;
	int out_floor;
	int give_up_time;
	string name;
}MAN_SPACE, *MAN;

typedef MAN Keytype;
const Keytype DEFAULT_KEY = NULL;

typedef struct List_node {
	Keytype data;
	struct List_node* next;
}LIST_NODE_SPACE, * LIST_NODE;

typedef struct List {
	int length;
	LIST_NODE head;
	LIST_NODE tail;
}LIST_SPACE, * LIST;

typedef struct Queue_node {
	Keytype data;
	struct Queue_node* next;
}QUEUE_NODE_SPACE, * QUEUE_NODE;

typedef struct Queue {
	QUEUE_NODE head;
	QUEUE_NODE tail;
	int length;
}QUEUE_SPACE, * QUEUE;

typedef struct {
	QUEUE waiting_queue[FLOOR_NUM][ELEVATOR_NUM];
	LIST elevator_list[ELEVATOR_NUM];
	int inter_time;
	int floor_num;
	int elevator_num;
}PEOPLE_SPACE, * PEOPLE;

void gotoxy(int x, int y);

void List_init(LIST& list);

void List_insert(LIST list, Keytype key);

void List_delete_node(LIST_NODE head, LIST_NODE deleted_node);

int List_empty(LIST list);

void List_show(LIST list);

void List_free(LIST& list);

void Queue_init(QUEUE& queue);

void Queue_push(QUEUE queue, Keytype key);

void Queue_pop(QUEUE queue);

Keytype Queue_front(QUEUE queue);

void Queue_show(QUEUE queue);

int Queue_empty(QUEUE queue);

void Queue_free(QUEUE& queue);

void error_message(string function_name, ERROR_TYPE error_type);

#endif

