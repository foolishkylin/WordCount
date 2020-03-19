#include "elevator.h"

void Set_window()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rc;
	rc.Left = 0;
	rc.Top = 0;
	rc.Right = rc.Left + 119;
	rc.Bottom = rc.Top + 79;
	//此时窗口的宽度为120，高度为80
	SetConsoleWindowInfo(hOut, TRUE, &rc);
	return ;
}

void Home()
{
	gotoxy(49, 4);
	cout << "电梯模拟系统";
	gotoxy(40, 1);
	cout << "_____________________________";
	gotoxy(40, 9);
	cout << "_____________________________";
	for (int i = 0; i < 8; i++)
	{
		gotoxy(40, 2 + i);
		cout << "|";
		gotoxy(68, 2 + i);
		cout << "|";
	}
	gotoxy(46, 6);
	cout << "班级: 软件工程一班";
	gotoxy(46, 7);
	cout << "学号: 3118004957";
	gotoxy(49, 8);
	cout << "姓名: 辜仰淦";

	gotoxy(30, 11);
	cout << "请输入电梯数（1-3）     \t:";
	gotoxy(30, 13);
	cout << "请输入楼层数（2-8）    \t:";
	gotoxy(30, 15);
	cout << "请输入电梯容量（1-20）  \t:";
	gotoxy(30, 17);
	cout << "请输入终止时间（50-5000）\t:";
	gotoxy(20, 19);
	cout << "若输入不合法则为默认模式（电梯数量为3, 楼层数为8, 电梯容量为5, 终止时间为500）";
	gotoxy(80, 20);
}

bool Isdigit(string input)
{
	for (int it = 0; it < input.length(); it++) 
		if (!isdigit(input[it]))
			return FALSE;
	return TRUE;
}

void GUI()
{
	Set_window();
	Home();
	int elevator_num = 3, floor_num = 8, capacity = 15, finished_time = 1500;
	string input = "";
	int num = 0;
	// 输入电梯数
	gotoxy(58, 11);
	cin >> input;
	if (Isdigit(input))
	{
		num = stoi(input);
		if (num > 0 && num < 3)
			elevator_num = num;
	}
	// 输入楼层数
	gotoxy(58, 13);
	cin >> input;
	if (Isdigit(input))
	{
		num = stoi(input);
		if (num > 1 && num < 9)
			floor_num = num;
	}
	// 输入电梯容量
	gotoxy(58, 15);
	cin >> input;
	if (Isdigit(input))
	{
		num = stoi(input);
		if (num > 0 && num < 21)
			capacity = num;
	}
	// 输入终止时间
	gotoxy(58, 17);
	cin >> input;
	if (Isdigit(input))
	{
		num = stoi(input);
		if (num > 49 && num < 5001)
			finished_time = num;
	}

	system("cls");
	ELEVATORS elevators = NULL;
	CLOCK clock = NULL;
	PEOPLE people = NULL;
	Elevators_init_user(people, elevators, clock, elevator_num, floor_num, capacity, finished_time);

	while (Timt_flow(people, elevators, clock) != ELEVATOR_STATUS::CUTOFF)
	{
		Event_flow(people, elevators, clock);
		UI(people, elevators, clock);
	}

	Elevators_free(people, elevators, clock);
	cin.clear();
	cin >> input;
	system("cls");
	GUI();

	return;
}

OPERATION_STATUS Event_flow(PEOPLE people, ELEVATORS elevators, CLOCK clock)
{
	for (int it = 0; it < elevators->elevator_num; it++)
	{
		ELEVATOR elevator = elevators->elevator[it];
		while (TRUE)
		{
			switch (elevator->event)
			{
			case EVENT::TIMED_ELEVATOR_UP:
				elevator->timer++;
				elevator->statement = "电梯上升中              ";
				if (elevator->timer >= SINGLE_FLOOR_UP)
				{
					elevator->timer = 0;
					elevator->current_floor++;
					//elevator->statement = "电梯上升完毕, 当前为" + to_string(elevator->current_floor) + "层";
					if (elevator->status == ELEVATOR_STATUS::IDLE_MOVING)
						// 若电梯在待机中，上升后则转电梯移动判断
						// 否则转电梯开门判断
						elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
					else
						elevator->event = EVENT::UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE;
				}
				break;
			case EVENT::TIMED_ELEVATOR_DOWN:
				elevator->timer++;
				elevator->statement = "电梯下降中              ";
				if (elevator->timer >= SINGLE_FLOOR_DOWN)
				{
					elevator->timer = 0;
					elevator->current_floor--;
					// elevator->statement = "电梯下降完毕";
					if (elevator->status == ELEVATOR_STATUS::IDLE_MOVING)
						// 若电梯在待机中，下降后则转电梯移动判断
						// 否则转电梯开门判断
						elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
					else
						elevator->event = EVENT::UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE;
				}
				break;
			case EVENT::TIMED_OPEN_DOOR:
				elevator->gate_status = GATE_STATUS::OPENING;
				elevator->timer++;
				elevator->statement = "电梯开门中              ";
				if (elevator->timer >= GATE_ACTIVITY_TIME)
				{
					elevator->timer = 0;
					elevator->gate_status = GATE_STATUS::OPENED;
					// elevator->statement = "电梯开门完毕";
					// 电梯开门完转人流判断
					elevator->event = EVENT::UNTIMED_PEOPLE_FLOW_JUDGE;
				}
				break;
			case EVENT::TIMED_PEOPLE_COME:
				elevator->timer++;
				elevator->statement = "有人进入                ";
				if (elevator->timer >= SINGLE_MAN_ACTIVITY)
				{
					elevator->timer = 0;
					// elevator->statement = "有人进入完毕";
					// 人进入完转人流判断
					elevator->event = EVENT::UNTIMED_PEOPLE_FLOW_JUDGE;
				}
				break;
			case EVENT::TIMED_PEOPLE_LEAVE:
				elevator->timer++;
				elevator->statement = "有人离开                ";
				if (elevator->timer >= SINGLE_MAN_ACTIVITY)
				{
					elevator->timer = 0;
					// elevator->statement = "有人离开完毕";
					// 人离开完转人流判断
					elevator->event = EVENT::UNTIMED_PEOPLE_FLOW_JUDGE;
				}
				break;
			case EVENT::TIMED_CLOSE_DOOR_TEST:
				elevator->timer++;
				elevator->statement = "关门测试中              ";
				// 此处判断是否有人来
				if (elevator->call_up[elevator->current_floor])
				{
					elevator->timer = 0;
					elevator->statement = "关门测试终止，有人前来  ";
					// 关门测试失败转人流判断
					elevator->event = EVENT::UNTIMED_PEOPLE_FLOW_JUDGE;
				}
				else if (elevator->timer >= SINGLE_MAN_ACTIVITY)
				{
					elevator->timer = 0;
					elevator->statement = "关门测试成功        ";
					// 关门测试成功转关门
					elevator->event = EVENT::TIMED_CLOSE_DOOR;
				}
				break;
			case EVENT::TIMED_CLOSE_DOOR:
				elevator->gate_status = GATE_STATUS::CLOSING;
				elevator->timer++;
				elevator->statement = "电梯关门中              ";
				if (elevator->call_up[elevator->current_floor] && elevator->capacity > people->elevator_list[it]->length)
				// 若当前有人来且电梯可容纳，转开门
				{
					elevator->timer = 0;
					elevator->statement = "关门终止，有人前来      ";
					// 关门测试失败转开门
					elevator->event = EVENT::TIMED_OPEN_DOOR;
				}
				else if (elevator->timer >= SINGLE_MAN_ACTIVITY)
				// 否则计时成功时，关门成功
				{
					elevator->timer = 0;
					elevator->statement = "关门测试成功            ";
					// 关门测试成功转电梯移动判断
					elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
				}
				break;
			case EVENT::TIMED_IDLE_TEST:
				elevator->timer++;
				elevator->statement = "电梯待机测试中          ";
				if (Elevator_move_judgment(elevator) == ELEVATOR_STATUS::UP ||
					Elevator_move_judgment(elevator) == ELEVATOR_STATUS::DOWN)
					elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
				else if (elevator->call_down[elevator->current_floor]
					|| elevator->call_up[elevator->current_floor]
					|| elevator->call_out[elevator->current_floor])
					elevator->event = EVENT::UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE;
				else if (elevator->timer >= IDLE_TEST)
				{
					elevator->timer = 0;
					elevator->statement = "电梯待机测试完毕        ";
					// 电梯待机测试成功转移动判断
					elevator->status = ELEVATOR_STATUS::IDLE_MOVING;
					elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
				}
				break;

			case EVENT::TIMED_IDLE:
				elevator->statement = "电梯待机中              ";
				if (Elevator_move_judgment(elevator) != ELEVATOR_STATUS::IDLE)
					elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
				if (elevator->call_down[elevator->current_floor]
					|| elevator->call_up[elevator->current_floor]
					|| elevator->call_out[elevator->current_floor])
					elevator->event = EVENT::UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE;
				break;

			case EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE:
				elevator->status = Elevator_move_judgment(elevator);
				switch (elevator->status)
				{
					case ELEVATOR_STATUS::UP:
					case ELEVATOR_STATUS::IDLE_UP:
						elevator->event = EVENT::TIMED_ELEVATOR_UP;
						break;
					case ELEVATOR_STATUS::DOWN:
					case ELEVATOR_STATUS::IDLE_DOWN:
						elevator->event = EVENT::TIMED_ELEVATOR_DOWN;
						break;
					case ELEVATOR_STATUS::IDLE:
						//若处于移动默认层判断，则判断后转电梯上升/下降
						elevator->event = EVENT::TIMED_IDLE;
						break;
					case ELEVATOR_STATUS::IDLE_TEST:
						elevator->event = EVENT::TIMED_IDLE_TEST;
							break;
					default: elevator->statement = "在移动判断处发生未知状态";
				}
				break;
			case EVENT::UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE:
				if (elevator->call_down[elevator->current_floor]
					|| elevator->call_up[elevator->current_floor]
					|| elevator->call_out[elevator->current_floor])
					// BUG:此处无法查询到呼叫
				{
					elevator->statement = "当前层有人呼叫          ";
					// 有人呼叫则开门
					elevator->event = EVENT::TIMED_OPEN_DOOR;
				}
				else
				{
					elevator->statement = "当前层无人呼叫          ";
					// 无人呼叫则转移动判断
					elevator->event = EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE;
				}
				break;
			case EVENT::UNTIMED_PEOPLE_FLOW_JUDGE:
				//先删除/插入人再计时
				//无人转关门测试
				if (Man_leave(people, elevator, it) == OPERATION_STATUS::SUCCESS)
					elevator->event = EVENT::TIMED_PEOPLE_LEAVE;
				else if (!Queue_empty(people->waiting_queue[elevator->current_floor][it]) && elevator->capacity > people->elevator_list[it]->length)
					// 若当前队列不空且电梯可容纳人进入，则让人进入
				{
					Man_enter(people, elevator, it);
					elevator->event = EVENT::TIMED_PEOPLE_COME;
				}
				else if (elevator->capacity <= people->elevator_list[it]->length)
					// 人满则关门
					elevator->event = EVENT::TIMED_CLOSE_DOOR;
				else 
					// 人未满，转关门测试
					elevator->event = EVENT::TIMED_CLOSE_DOOR_TEST;
				// 人走完后取消呼叫
				if (!people->elevator_list[it]->length)
					elevator->call_out[elevator->current_floor] = FALSE;
				if (Queue_empty(people->waiting_queue[elevator->current_floor][it]))
				{
					elevator->call_up[elevator->current_floor] = FALSE;
					elevator->call_down[elevator->current_floor] = FALSE;
				}
				break;
			default: elevator->statement = "事件流出现未知状态";
			}
			if (elevator->event == EVENT::UNTIMED_ELEVATOR_MOVE_JUDGE ||
				elevator->event == EVENT::UNTIMED_ELEVATOR_OPEN_DOOR_JUDGE ||
				elevator->event == EVENT::UNTIMED_PEOPLE_FLOW_JUDGE)
				continue;
			else
				break;
		}
	}
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Man_leave(PEOPLE people, ELEVATOR elevator, int elevator_id)
{
	LIST list = people->elevator_list[elevator_id];
	if (!list)
	{
		error_message("List_delete", ERROR_TYPE::NULL_PTR);
		return OPERATION_STATUS::FAIL;
	}
	if (!list->length)
		return OPERATION_STATUS::FAIL;
	bool not_deleted = TRUE;
	LIST_NODE it = list->head;
	while (not_deleted && it)
		if (it->data->out_floor == elevator->current_floor)
		{
			if (list->length == 1)
			{
				free(list->head);
				list->head = list->tail = NULL;
				it = NULL;
				not_deleted = FALSE;
			}
			else if (it == list->head)
			{
				list->head = list->head->next;
				free(it);
				it = list->head;
				not_deleted = FALSE;
			}
			else
			{
				not_deleted = FALSE;
				if (it == list->tail)
				{
					LIST_NODE new_tail;
					for (new_tail = list->head; new_tail->next != list->tail; new_tail = new_tail->next);
					list->tail = new_tail;
					List_delete_node(list->head, it);
					it = NULL;
				}
				else
				{
					LIST_NODE nit = it->next;
					List_delete_node(list->head, it);
					it = nit;
				}
			}
			list->length--;
		}
		else
			it = it->next;
	if (not_deleted)
		return OPERATION_STATUS::FAIL;
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Man_enter(PEOPLE people, ELEVATOR elevator, int elevator_id)
{
	MAN man;
	man = Queue_front(people->waiting_queue[elevator->current_floor][elevator_id]);
	// 人按下离开电梯的按钮
	Man_push_leave_button(man, elevator);
	List_insert(people->elevator_list[elevator_id], man);
	Queue_pop(people->waiting_queue[elevator->current_floor][elevator_id]);
	
	return OPERATION_STATUS::SUCCESS;
}

ELEVATOR_STATUS Elevator_move_judgment(ELEVATOR elevator)
{
	int floor;
	switch (elevator->status)
	{
		case ELEVATOR_STATUS::UP:
			// 当电梯往上移动时，优先回应当前层以上的呼叫
			for (floor = elevator->current_floor + 1; floor < elevator->floor_num; floor++)
				if (elevator->call_up[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::UP;
			for (floor = elevator->current_floor - 1; floor >= 0; floor--)
				if (elevator->call_down[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::DOWN;

			// 判断是否需要待机测试
			if (elevator->current_floor == DEFAULT_FLOOR)
				return ELEVATOR_STATUS::IDLE;
			else
				return ELEVATOR_STATUS::IDLE_TEST;

		case ELEVATOR_STATUS::DOWN:
			// 当电梯往下移动时，优先回应当前层以下的呼叫
			for (floor = elevator->current_floor - 1; floor >= 0; floor--)
				if (elevator->call_down[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::DOWN;
			for (floor = elevator->current_floor + 1; floor < elevator->floor_num; floor++)
				if (elevator->call_up[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::UP;

			// 判断是否需要待机测试
			if (elevator->current_floor == DEFAULT_FLOOR)
				return ELEVATOR_STATUS::IDLE;
			else
				return ELEVATOR_STATUS::IDLE_TEST;

		case ELEVATOR_STATUS::IDLE:
			// 电梯此时处于待机状态中，判断是否需要进行待机
			for (floor = elevator->current_floor - 1; floor >= 0; floor--)
				if (elevator->call_down[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::DOWN;
			for (floor = elevator->current_floor + 1; floor < elevator->floor_num; floor++)
				if (elevator->call_up[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::UP;
			return ELEVATOR_STATUS::IDLE;

		case ELEVATOR_STATUS::IDLE_MOVING:
		case ELEVATOR_STATUS::IDLE_UP:
		case ELEVATOR_STATUS::IDLE_DOWN:			
			// 若此时有人呼叫，则优先处理呼叫
			for (floor = elevator->current_floor - 1; floor >= 0; floor--)
				if (elevator->call_down[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::DOWN;
			for (floor = elevator->current_floor + 1; floor < elevator->floor_num; floor++)
				if (elevator->call_up[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::UP;
			// 否则往默认层移动,若在默认层则转待机
			if (elevator->current_floor == DEFAULT_FLOOR)
				return ELEVATOR_STATUS::IDLE;
			else if (elevator->current_floor > DEFAULT_FLOOR)
				return ELEVATOR_STATUS::IDLE_DOWN;
			else
				return ELEVATOR_STATUS::IDLE_UP;
		case ELEVATOR_STATUS::IDLE_TEST:
			for (floor = elevator->current_floor - 1; floor >= 0; floor--)
				if (elevator->call_down[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::DOWN;
			for (floor = elevator->current_floor + 1; floor < elevator->floor_num; floor++)
				if (elevator->call_up[floor] || elevator->call_out[floor])
					return ELEVATOR_STATUS::UP;
			return ELEVATOR_STATUS::IDLE_TEST;
		default: cout << "在电梯移动判断出现未知情况";
	}
	return ELEVATOR_STATUS::IDLE;
}

void UI(PEOPLE people, ELEVATORS elevators, CLOCK clock)
{
	int layer, it, nit;
	int gap = 40;
	gotoxy(0, 0);
	cout << "当前时间/终止时间: " << clock->current_time+1 << "/" << clock->finish_time;

	for (it = 0; it < elevators->elevator_num; it++)
	{
		// 打印框架
		layer = 2;
		gotoxy(it * gap, layer);
		cout << "//--                --//" ;
		gotoxy(it * gap + 8, layer++);
		switch (it)
		{
			case 0: cout << "一号电梯"; break;
			case 1: cout << "二号电梯"; break;
			case 2: cout << "三号电梯"; break;
			default: cout << "未知电梯";
		}
		for (int nit = 0; nit < people->floor_num; nit++)
		{
			gotoxy(it * gap, layer++);
			cout << "////////////////////////";
			gotoxy(it * gap, layer++);
			cout << "////                ////";
			gotoxy(it * gap, layer++);
			cout << "////                ////";
		}
		gotoxy(it * gap, layer++);
		cout << "////////////////////////";

		// 打印电梯
		gotoxy(it * gap + 9, 2 + (people->floor_num - elevators->elevator[it]->current_floor) * 3);
		cout << "【 " + to_string(people->elevator_list[it]->length) + " 】";

		gotoxy(it * gap, layer);
		cout << elevators->elevator[it]->statement;
		// 打印等待队列
		for (nit = 0; nit < people->floor_num; nit++)
		{
			gotoxy(it * gap + 27, 2 + (people->floor_num - nit) * 3);
			cout << to_string(people->waiting_queue[nit][it]->length) + "人等候";
		}
	}
}

OPERATION_STATUS Elevators_generate(ELEVATORS& elevators)
{
	elevators = new ELEVATORS_SPACE;
	if (!elevators)
		return OPERATION_STATUS::FAIL;
	for (int i = 0; i < ELEVATOR_NUM; i++)
	{
		elevators->elevator[i] = new ELEVATOR_SPACE;
		if (elevators->elevator[i])
		{
			elevators->elevator[i]->statement = "";
			memset(elevators->elevator[i]->call_up, 0, sizeof(elevators->elevator[i]->call_up));
			memset(elevators->elevator[i]->call_down, 0, sizeof(elevators->elevator[i]->call_down));
			memset(elevators->elevator[i]->call_out, 0, sizeof(elevators->elevator[i]->call_out));
			elevators->elevator[i]->capacity = ELEVATOR_CAPACITY;
			elevators->elevator[i]->current_floor = DEFAULT_FLOOR;
			elevators->elevator[i]->status = ELEVATOR_STATUS::IDLE;
			elevators->elevator[i]->timer = 0;
			elevators->elevator[i]->gate_status = GATE_STATUS::CLOSED;
			elevators->elevator[i]->people_flow = FALSE;
			elevators->elevator[i]->event = EVENT::TIMED_IDLE;
		}
		else
			OPERATION_STATUS::FAIL;
	}
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Elevators_init(PEOPLE& people, ELEVATORS& elevators, CLOCK& clock)
{
	Elevators_generate(elevators);
	Clock_set(clock);
	People_set(people, clock);
	return OPERATION_STATUS::SUCCESS;
}

OPERATION_STATUS Elevators_free(PEOPLE people, ELEVATORS elevators, CLOCK clock)
{
	if (!people || !elevators || !clock)
	{
		error_message("Elevators_free", ERROR_TYPE::NULL_PTR);
		return OPERATION_STATUS::FAIL;
	}
	int it, nit;
	for (it = 0; it < ELEVATOR_NUM; it++)
	{
		if (elevators->elevator[it])
			delete elevators->elevator[it];
		if (people->elevator_list[it])
			List_free(people->elevator_list[it]);
	}
	delete elevators;
	for (it = 0; it < FLOOR_NUM; it++)
		for (nit = 0; nit < ELEVATOR_NUM; nit++)
			if (people->waiting_queue[it][nit])
				Queue_free(people->waiting_queue[it][nit]);
	free(people);
	free(clock);
	return OPERATION_STATUS::SUCCESS;
}

ELEVATOR_STATUS Timt_flow(PEOPLE people, ELEVATORS elevators, CLOCK clock)
{
	Sleep(100);
	clock->current_time ++;
	if (clock->current_time >= people->inter_time)
		Man_generate(people, elevators, clock);
	Man_leave(people, clock);
	if (clock->current_time >= clock->finish_time)
		return ELEVATOR_STATUS::CUTOFF;
	return ELEVATOR_STATUS::OPERATING;
}

OPERATION_STATUS Elevators_init_user(PEOPLE& people, ELEVATORS& elevators, CLOCK& clock,
	int elevator_num, int floor_num, int capacity, int finished_time)
{
	elevators = new ELEVATORS_SPACE;
	if (!elevators)
		return OPERATION_STATUS::FAIL;
	elevators->elevator_num = elevator_num;
	for (int i = 0; i < ELEVATOR_NUM; i++)
	{
		elevators->elevator[i] = new ELEVATOR_SPACE;
		if (elevators->elevator[i])
		{
			elevators->elevator[i]->statement = "";
			memset(elevators->elevator[i]->call_up, 0, sizeof(elevators->elevator[i]->call_up));
			memset(elevators->elevator[i]->call_down, 0, sizeof(elevators->elevator[i]->call_down));
			memset(elevators->elevator[i]->call_out, 0, sizeof(elevators->elevator[i]->call_out));
			elevators->elevator[i]->capacity = capacity;
			elevators->elevator[i]->current_floor = DEFAULT_FLOOR;
			elevators->elevator[i]->status = ELEVATOR_STATUS::IDLE;
			elevators->elevator[i]->timer = 0;
			elevators->elevator[i]->floor_num = floor_num;
			elevators->elevator[i]->gate_status = GATE_STATUS::CLOSED;
			elevators->elevator[i]->people_flow = FALSE;
			elevators->elevator[i]->event = EVENT::TIMED_IDLE;
		}
		else
			OPERATION_STATUS::FAIL;
	}

	clock = (CLOCK)malloc(sizeof(CLOCK_SPACE));
	if (clock)
	{
		clock->current_time = 0;
		clock->finish_time = finished_time;
	}
	else
		return OPERATION_STATUS::FAIL;

	people = (PEOPLE)malloc(sizeof(PEOPLE_SPACE));
	if (people)
	{
		people->floor_num = floor_num;
		people->elevator_num = elevator_num;
		int it;
		for (it = 0; it < ELEVATOR_NUM; it++)
			List_init(people->elevator_list[it]);
		for (it = 0; it < FLOOR_NUM; it++)
			for (int nit = 0; nit < ELEVATOR_NUM; nit++)
				Queue_init(people->waiting_queue[it][nit]);
		people->inter_time = 0;

	}
	else 	
		return OPERATION_STATUS::FAIL;

	return OPERATION_STATUS::SUCCESS;
}