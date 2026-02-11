#ifndef RP2040_MEMORY_H
#define RP2040_MEMORY_H

#include <rp2040/common.h>

#define SRAM_Bank_0 0x2000'0000
#define SRAM_Bank_1 0x2001'0000
#define SRAM_Bank_2 0x2002'0000
#define SRAM_Bank_3 0x2003'0000
#define SRAM_Bank_4 0x2004'0000
#define SRAM_Bank_5 0x2004'1000

enum Memory_Bank_Bits : uint8_t
{
	SRAM_0     = (1 << 0),
	SRAM_1     = (1 << 1),
	SRAM_2     = (1 << 2),
	SRAM_3     = (1 << 3),
	SRAM_4     = (1 << 4),
	SRAM_5     = (1 << 5),
	USB_Memory = (1 << 6),
	ROM_Memory = (1 << 7)
};

void Disable_Memory_Bank (enum Memory_Bank_Bits Which);
void Enable_Memory_Bank (enum Memory_Bank_Bits Which);

#endif /* RP2040_MEMORY_H */
