#ifndef RP2040_TIMER_H
#define RP2040_TIMER_H

#include <rp2040/common.h>

enum Alarm_Bits : uint8_t
{
	Alarm_0 = (1 << 0),
	Alarm_1 = (1 << 1),
	Alarm_2 = (1 << 2),
	Alarm_3 = (1 << 3)
};

void Time (uint32_t *Low, uint32_t *High);
void Pause (bool Should_Pause);

void Enable_Alarm (enum Alarm_Bits Alarms);
void Disable_Alarm (enum Alarm_Bits Alarms);

void Force_Trigger_Alarm (enum Alarm_Bits Alarms);
void Set_Alarm_0 (uint32_t Time);
void Set_Alarm_1 (uint32_t Time);
void Set_Alarm_2 (uint32_t Time);
void Set_Alarm_3 (uint32_t Time);

bool Alarm_Is_Armed (enum Alarm_Bits Alarms);

#endif /* RP2040_TIMER_H */
