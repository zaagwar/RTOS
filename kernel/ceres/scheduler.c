#include <ceres/scheduler.h>

uint8_t    n_Tasks = 0;
struct TCB Tasks[MAX_TASKS];

void Initialize_Scheduler (void)
{
	for ( uint8_t i = 0; i < MAX_TASKS; ++i )
		Tasks[i].State = Task_Dead;
}

int32_t Create_Task (char *Name, uint32_t Priority, void *(*Entry)(void*))
{
	if ( n_Tasks == MAX_TASKS )
		return e_Too_Many_Tasks;

	uint8_t Available_Task_ID;
	bool    Found = false;
	for ( uint8_t i = 0; i < MAX_TASKS; ++i )
	{
		if ( Tasks[i].State == Task_Dead )
		{
			Found = true;
			Available_Task_ID = i;
			break;
		}
	}

	if ( !Found )
		return e_Too_Many_Tasks;

	Tasks[Available_Task_ID] =
	(struct TCB) {
		.Priority = Priority,
		.State    = Task_Ready,

		.Name     = Name,
		.ID       = Available_Task_ID,

		/* Avoid implicit `memset` on GCC cross-compilers.
		 * GCC still puts implicit libc function calls in code compiled with
		 * `-fno-builtin` when using `-flto`. This is a cheap workaround.
		 */
		.PSP      = 0xDEAD'BEEF,
		.MSP      = 0xDEAD'BEEF,
		.PC       = (uint32_t) Entry,
		.LR       = 0xFFFF'FFFE,
		.PSR      = 0x0B00'B1E5,

		.PRIMASK  = 0,
		.CONTROL  = 0,

		.R0       = 0,
		.R1       = 0,
		.R2       = 0,
		.R3       = 0,
		.R4       = 0,
		.R5       = 0,
		.R6       = 0,
		.R7       = 0,
		.R8       = 0,
		.R9       = 0,
		.R10      = 0,
		.R11      = 0,
		.R12      = 0
	};

	++n_Tasks;
	return Available_Task_ID;
}

bool Delete_Task (const uint8_t ID)
{
	if ( ID >= MAX_TASKS ) return false;

	else if ( Tasks[ID].State != Task_Dead )
	{
		Tasks[ID].State = Task_Dead;
		return true;
	}

	else return false;
}

bool Restart_Task (const uint8_t ID);
bool Suspend_Task (const uint8_t ID);
bool Resume_Task (const uint8_t ID);

void     Get_Task_ID (void);
void     Get_Task_Name (const uint8_t ID);
uint32_t Get_Task_Priority (const uint8_t ID);
bool     Set_Task_Priority (const uint8_t ID);

bool Acquire_Preemption_Lock (void);
bool Release_Preemption_Lock (void);
