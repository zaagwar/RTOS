#ifndef CERES_SCHED_H
#define CERES_SCHED_H

#include <ceres/common.h>
#include <ceres/dispatcher.h>

#define MAX_TASKS 16

#define e_Too_Many_Tasks -1

enum Task_State : uint8_t
{
	Task_Ready = 0,
	Task_Blocked,
	Task_Running,
	Task_Dead  = UINT8_MAX
};

struct TCB
{
	/* Information for dispatcher */
	uint8_t         Priority;
	enum Task_State State;

	/* Task identifying information */
	char   *Name;
	uint8_t ID;

	uint32_t PSP; /* Process Stack Pointer */
	uint32_t MSP; /* Main Stack Pointer */
	uint32_t PC;  /* Program Counter */
	uint32_t LR;  /* Link Register */
	uint32_t PSR; /* Program Status Register */

	uint32_t PRIMASK;
	uint32_t CONTROL; 

	/* General purpose registers */
	uint32_t R0;
	uint32_t R1;
	uint32_t R2;
	uint32_t R3;
	uint32_t R4;
	uint32_t R5;
	uint32_t R6;
	uint32_t R7;
	uint32_t R8;
	uint32_t R9;
	uint32_t R10;
	uint32_t R11;
	uint32_t R12;
} __attribute__ (( aligned ));

extern uint8_t    n_Tasks;
extern struct TCB Tasks[MAX_TASKS];

void Initialize_Scheduler (void);

/* Control the number of tasks. */
int32_t Create_Task (char *Name, uint32_t Priority, void *(*Entry)(void*));
bool    Delete_Task (const uint8_t ID);

/* Control the execution of a task. */
bool Restart_Task (const uint8_t ID);
bool Suspend_Task (const uint8_t ID);
bool Resume_Task (const uint8_t ID);

/* Get information about a task. */
void     Get_Task_ID (void);
void     Get_Task_Name (const uint8_t ID);
uint32_t Get_Task_Priority (const uint8_t ID);
bool     Set_Task_Priority (const uint8_t ID);

/* Enables/disables preemption by higher priority tasks. */
bool Acquire_Preemption_Lock (void);
bool Release_Preemption_Lock (void);

#endif /* CERES_SCHED_H */
