/* Raspberry Pi Pico (RP2040) */
#include <rp2040/common.h>
#include <rp2040/mailbox.h>
#include <rp2040/gpio.h>
#include <rp2040/smp.h>

/* ARM Cortex-M0+ (ARMv6-M) */
#include <cortex-m0plus/common.h>
//#include <cortex-m0plus/systick.h>
#include <cortex-m0plus/nvic.h>
//#include <cortex-m0plus/wic.h>
//#include <cortex-m0plus/mpu.h>

/* RP2040-specific
 *
 * (-) ADC
 * (-) BUSCTL
 * (-) DMA
 * (-) I2C
 * (-) Interpolators
 * (+) GPIO
 * (-) QSPI
 * (-) JTAG
 * (-) PIO
 * (-) PLL
 * (-) PWM
 * (-) Regulator
 * (-) RTC
 * (-) SPI
 * (-) Spinlocks
 * (-) SYSCFG
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
 * (-) NVIC
 * (-) Tasks
 * (-) Scheduling
 * (-) Semaphores
 */

static void Main (void);

void Secondary_Entry (void)
{
	while ( true ) { _ARMv6M_WFI; }
}

void Start_Kernel (void)
{
	RP2040_Enable_Subsystem(GPIO);

	{
		/* Very last 16-byte aligned memory in SRAM4. */
		const uintptr_t Primary_Stack = 0x2004'0FF0;

		Primary_IVT[0] = (void(*)(void))Primary_Stack;
		Set_Vector_Table(Primary_IVT);
	}

	/* Start the other core. */
	{
		/* Very last 16-byte aligned memory in SRAM5. */
		const uintptr_t Secondary_Stack = 0x2004'1FF0;
		
		Secondary_IVT[0] = (void(*)(void))Secondary_Stack;
		Start_Other_Core(Secondary_IVT, Secondary_Entry, Secondary_Stack);

		if ( Active_Cores == 0b0000'0011 )
		{
			RP2040_GPIO_Select_Port_Function(Port_25, Port_Function_SIO);
			RP2040_GPIO_Enable_Port(Port_25, Port_Direction_Output);
			RP2040_GPIO_Drive_Port(Port_25, Port_Output_High);
		}
	}

	Main();
}

void Main (void)
{
	while ( true ) { _ARMv6M_WFI; }
}
