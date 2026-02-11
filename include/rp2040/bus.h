#ifndef RP2040_BUS_H
#define RP2040_BUS_H

#include <rp2040/common.h>

enum Bus_Master_Bits : uint16_t
{
	Core_0_Bus    = (1 << 0),
	Core_1_Bus    = (1 << 4),
	DMA_Read_Bus  = (1 << 8),
	DMA_Write_Bus = (1 << 12)
};

void Set_Bus_Priority_High (enum Bus_Master_Bits Bus_Master_Bits);
void Set_Bus_Priority_Low (enum Bus_Master_Bits Bus_Master_Bits);

#endif /* RP2040_BUS_H */
