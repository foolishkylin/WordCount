#include "clock.h"

OPERATION_STATUS Clock_set(CLOCK& clock)
{
	clock = (CLOCK)malloc(sizeof(CLOCK_SPACE));
	if (clock)
	{
		clock->current_time = 0;
		clock->finish_time = FINISHED_TIME;
		return OPERATION_STATUS::SUCCESS;
	}

	return OPERATION_STATUS::FAIL;
}
