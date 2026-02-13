#include <rp2040/timer.h>

/* NOTE: Crude. TODO: Robust. */
void Time (uint32_t *Low, uint32_t *High)
{
	const uint32_t r_Time_Raw_High = 0x4005'4024;
	const uint32_t r_Time_Raw_Low  = 0x4005'4028;

	*Low  = Rd32(r_Time_Raw_Low);
	*High = Rd32(r_Time_Raw_High);
}

void Pause (bool Should_Pause)
{
	const uint32_t r_Timer_Pause = 0x4005'4030;
	Wr8(r_Timer_Pause, Should_Pause);
}

void Enable_Alarm (enum Alarm_Bits Alarms)
{
	const uint32_t r_Timer_Interrupt_Enable = 0x4005'4038;
	Wr8(r_Timer_Interrupt_Enable | Atomic_Set, Alarms);
}

void Disable_Alarm (enum Alarm_Bits Alarms)
{
	const uint32_t r_Timer_Interrupt_Enable = 0x4005'4038;
	Wr8(r_Timer_Interrupt_Enable | Atomic_Clear, Alarms);
}

void Force_Trigger_Alarm (enum Alarm_Bits Alarms)
{
	const uint32_t r_Timer_Interrupt_Force = 0x4005'403C;
	Wr8(r_Timer_Interrupt_Force | Atomic_Set, Alarms);
}

void Set_Alarm_0 (uint32_t Time)
{
	const uint32_t r_Timer_Alarm_0 = 0x4005'4010;
	Wr32(r_Timer_Alarm_0, Time);
}

void Set_Alarm_1 (uint32_t Time)
{
	const uint32_t r_Timer_Alarm_1 = 0x4005'4014;
	Wr32(r_Timer_Alarm_1, Time);
}

void Set_Alarm_2 (uint32_t Time)
{
	const uint32_t r_Timer_Alarm_2 = 0x4005'4018;
	Wr32(r_Timer_Alarm_2, Time);
}

void Set_Alarm_3 (uint32_t Time)
{
	const uint32_t r_Timer_Alarm_3 = 0x4005'401C;
	Wr32(r_Timer_Alarm_3, Time);
}

bool Alarm_Is_Armed (enum Alarm_Bits Alarms)
{
	const uint32_t r_Alarm_Armed = 0x4005'4020;
	return (Rd8(r_Alarm_Armed) & Alarms) == Alarms;
}
