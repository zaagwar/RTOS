#ifndef RP2040_COMMON_H
#define RP2040_COMMON_H

#include <common.h>
#include <rp2040/cortex-m0plus.h>

#define Atomic_Clear 0x3000
#define Atomic_Set   0x2000
#define Atomic_Flip  0x1000

enum Subsystem : uint32_t
{
	ADC       = (1 << 0),
	BUSCTL    = (1 << 1),
	DMA       = (1 << 2),
	I2C_0     = (1 << 3),
	I2C_1     = (1 << 4),
	GPIO      = (1 << 5),
	QSPI      = (1 << 6),
	JTAG      = (1 << 7),
	GPIO_PADS = (1 << 8),
	QSPI_PADS = (1 << 9),
	PIO_0     = (1 << 10),
	PIO_1     = (1 << 11),
	PLL_SYS   = (1 << 12),
	PLL_USB   = (1 << 13),
	PWM       = (1 << 14),
	RTC       = (1 << 15),
	SPI_0     = (1 << 16),
	SPI_1     = (1 << 17),
	SYSCFG    = (1 << 18),
	SYSINFO   = (1 << 19), /* Do not use */
	TBMAN     = (1 << 20), /* Do not use */
	TIMER     = (1 << 21),
	UART_0    = (1 << 22),
	UART_1    = (1 << 23),
	USB       = (1 << 24)
};

void RP2040_Enable_Subsystem (const uint32_t Subsystems);

#endif /* RP2040_COMMON_H */
