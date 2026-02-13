#ifndef CORTEX_M0PLUS_NVIC_H
#define CORTEX_M0PLUS_NVIC_H

#include <rp2040/cortex-m0plus.h>

extern __attribute__ (( aligned(256) )) void (*Primary_IVT[48])(void);
extern __attribute__ (( aligned(256) )) void (*Secondary_IVT[48])(void);

enum IRQ_Bits : uint32_t
{
	Timer_IRQ_0     = (1 << 0),
	Timer_IRQ_1     = (1 << 1),
	Timer_IRQ_2     = (1 << 2),
	Timer_IRQ_3     = (1 << 3),
	PWM_IRQ_Wrap    = (1 << 4),
	USB_Control_IRQ = (1 << 5),
	XIP_IRQ         = (1 << 6),
	PIO_0_IRQ_0     = (1 << 7),
	PIO_0_IRQ_1     = (1 << 8),
	PIO_1_IRQ_0     = (1 << 9),
	PIO_1_IRQ_1     = (1 << 10),
	DMA_IRQ_0       = (1 << 11),
	DMA_IRQ_1       = (1 << 12),
	IO_IRQ_BANK_0   = (1 << 13),
	IO_IRQ_QSPI     = (1 << 14),
	SIO_IRQ_PROC_0  = (1 << 15),
	SIO_IRQ_PROC_1  = (1 << 16),
	Clocks_IRQ      = (1 << 17),
	SPI_0_IRQ       = (1 << 18),
	SPI_1_IRQ       = (1 << 19),
	UART_0_IRQ      = (1 << 20),
	UART_1_IRQ      = (1 << 21),
	ADC_IRQ_FIFO    = (1 << 22),
	I2C_0_IRQ       = (1 << 23),
	I2C_1_IRQ       = (1 << 24),
	RTC_IRQ         = (1 << 25),
	All_Interrupts  = UINT32_MAX
};

enum Interrupt_Priority : uint8_t
{
	Utmost_Priority = 0,
	High_Priority,
	Medium_Priority,
	Low_Priority
};

void Set_Vector_Table (void (*Vector_Table[48])(void));
void Set_ISR (void (**IVT)(void), enum IRQ_Bits IRQ, void (*ISR)(void));

void Enable_Interrupt (enum IRQ_Bits IRQ_Bits);
void Disable_Interrupt (enum IRQ_Bits IRQ_Bits);

void Pend_Interrupt (enum IRQ_Bits IRQ_Bits);
void Unpend_Interrupt (enum IRQ_Bits IRQ_Bits);

void Set_Interrupt_Priority (
	enum IRQ_Bits           IRQ_Bits,
	enum Interrupt_Priority Priority
);

#endif /* CORTEX_M0PLUS_NVIC_H */
