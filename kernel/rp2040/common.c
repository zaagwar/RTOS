#include <rp2040/common.h>

void RP2040_Enable_Subsystem (const uint32_t Subsystems)
{
	const uint32_t r_Reset_Subsystem     = 0x4000'C000;
	const uint32_t r_Reset_Subsystem_Ack = 0x4000'C008;

	Wr32(r_Reset_Subsystem | Atomic_Clear, Subsystems);
	while ( (Rd32(r_Reset_Subsystem_Ack) & Subsystems) != Subsystems );
}
