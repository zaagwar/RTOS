#include <rp2040/bus.h>

const uint32_t r_Bus_Priority     = 0x4003'0000;
const uint32_t r_Bus_Priority_Ack = 0x4003'0004;

void Set_Bus_Priority_High (enum Bus_Master_Bits Bus_Master_Bits)
{
	/* Write the bits to set and poll the acknowledgement bit. */
	Wr16(r_Bus_Priority | Atomic_Set, Bus_Master_Bits);
	while ((Rd8(r_Bus_Priority_Ack) & 1) == 0);
}

void Set_Bus_Priority_Low (enum Bus_Master_Bits Bus_Master_Bits)
{
	/* Write the bits to clear and poll the acknowledgement bit. */
	Wr16(r_Bus_Priority | Atomic_Clear, Bus_Master_Bits);
	while ((Rd8(r_Bus_Priority_Ack) & 1) == 0);
}
