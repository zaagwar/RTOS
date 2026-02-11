/* Raspberry Pi Pico (RP2040) */
#include <rp2040/common.h>
#include <rp2040/regulator.h>
#include <rp2040/mailbox.h>
#include <rp2040/memory.h>
#include <rp2040/gpio.h>
#include <rp2040/smp.h>
#include <rp2040/bus.h>

/* ARM Cortex-M0+ (ARMv6-M) */
#include <cortex-m0plus/common.h>
//#include <cortex-m0plus/systick.h>
#include <cortex-m0plus/nvic.h>
#include <cortex-m0plus/mpu.h>

/* SRAM0 (64 KiB)
 *   [0x2000'0000, 0x2000'2000) : .Text
 * SRAM1 (64 KiB)
 *   [0x2001'0000, 0x2001'1000) : .Data
 * SRAM2 (64 KiB)
 *   [0x2002'0000, 0x2003'0000) : Task memory
 * SRAM3 (64 KiB)
 *   [0x2003'0000, 0x2003'1000) : .BSS
 * SRAM4 (4 KiB)
 *   [0x2004'0000, 0x2004'1000) : Primary_Stack
 * SRAM5 (4 KiB)
 *   [0x2004'1000, 0x2004'2000) : Secondary_Stack
 */

/* RP2040-specific
 *
 * (-) ADC
 * (+) BUSCTL
 * (-) DMA
 * (-) I2C
 * (-) Interpolators
 * (+) GPIO
 * (-) QSPI
 * (-) JTAG
 * (-) PIO
 * (-) PLL
 * (-) PWM
 * (+) Regulator
 * (-) RTC
 * (-) SPI
 * (-) Spinlocks
 * (+) SYSCFG
 * (-) Timer
 * (-) UART
 * (-) USB
 * (-) Watchdog
 *
 * (-) Floating-point library
 * (-) Memory library
 */

/* Cortex-M0+ and RTOS
 *
 * (+) SMP
 * (-) IPC
 * (-) MPU
 * (+) NVIC
 * (-) Tasks
 * (-) File system
 * (-) Scheduling
 * (-) Semaphores
 * (-) Dynamic allocation
 */

void Secondary_Entry (void)
{
	while ( true ) { _ARMv6M_WFI; }
}

void Init (void)
{
	RP2040_Enable_Subsystem(GPIO | SYSCFG);


	/* Initialize the primary core's interrupt vector table. */
	{
		/* Very last 16-byte aligned memory in SRAM4. */
		const uintptr_t Primary_Stack = 0x2004'0FF0;

		Primary_IVT[0] = (void(*)(void))Primary_Stack;
		Set_Vector_Table(Primary_IVT);
	}

	/* Start the secondary core. */
	{
		/* Very last 16-byte aligned memory in SRAM5. */
		const uintptr_t Secondary_Stack = 0x2004'1FF0;
		
		Secondary_IVT[0] = (void(*)(void))Secondary_Stack;
		Start_Other_Core(Secondary_IVT, Secondary_Entry, Secondary_Stack);
	}

	Main();
}

void Main (void)
{
	/* Configure priorities. */
	Set_Bus_Priority_High(Core_0_Bus | Core_1_Bus);

	/* Configure internal voltage regulator. */
	Set_Regulator_Voltage(Voltage_1_00);

	RP2040_GPIO_Select_Port_Function(Port_25, Port_Function_SIO);
	RP2040_GPIO_Enable_Port(Port_25, Port_Direction_Output);
	RP2040_GPIO_Drive_Port(Port_25, Port_Output_High);

	while ( true ) { _ARMv6M_WFI; }
}
