#include <rp2040/memory.h>

void Disable_Memory_Bank (enum Memory_Bank_Bits Which)
{
	const uint32_t r_Power_Down_Memory = 0x4000'4018;
	Wr8(r_Power_Down_Memory | Atomic_Set, Which);
}

void Enable_Memory_Bank (enum Memory_Bank_Bits Which)
{
	const uint32_t r_Processor_Config = 0x4000'4008;
	Wr8(r_Processor_Config | Atomic_Clear, Which);
}
