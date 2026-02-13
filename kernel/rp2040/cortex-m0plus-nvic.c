#include <rp2040/cortex-m0plus-nvic.h>

__attribute__ (( aligned(256) )) void (*Primary_IVT[48])(void);
__attribute__ (( aligned(256) )) void (*Secondary_IVT[48])(void);
/*
{
	[0]  = (void(*)(void))Secondary_Stack,
	[1]  = Reset_Handler,
	[2]  = NMI_Handler,
   	[3]  = Hard_Fault_Handler,
   	[4]  = nullptr,
   	[5]  = nullptr,
   	[6]  = nullptr,
   	[7]  = nullptr,
   	[8]  = nullptr,
   	[9]  = nullptr,
   	[10] = nullptr,
   	[11] = SV_Call_Handler,
   	[12] = nullptr,
   	[13] = nullptr,
   	[14] = Pend_SV_Handler,
   	[15] = SysTick_Handler,
   	[16] = 
};
*/

void Enable_Interrupt (enum IRQ_Bits IRQ_Bits)
{
	const uint32_t r_NVIC_Enable_IRQ = 0xE000'E100;

	Wr32(r_NVIC_Enable_IRQ, IRQ_Bits);
	while ((Rd32(r_NVIC_Enable_IRQ) & IRQ_Bits) != IRQ_Bits);
}

void Disable_Interrupt (enum IRQ_Bits IRQ_Bits)
{
	const uint32_t r_NVIC_Disable_IRQ = 0xE000'E180;

	Wr32(r_NVIC_Disable_IRQ, IRQ_Bits);
	while (Rd32(r_NVIC_Disable_IRQ) & IRQ_Bits);
}

void Pend_Interrupt (enum IRQ_Bits IRQ_Bits)
{
	const uint32_t r_NVIC_Pend_IRQ = 0xE000'E200;
	Wr32(r_NVIC_Pend_IRQ, IRQ_Bits);
}

void Unpend_Interrupt (enum IRQ_Bits IRQ_Bits)
{
	const uint32_t r_NVIC_Unpend_IRQ = 0xE000'E280;
	Wr32(r_NVIC_Unpend_IRQ, IRQ_Bits);
}

void Set_Vector_Table (void (*Vector_Table[48])(void))
{
	const uint32_t r_VTOR = 0xE000'ED08;
	Wr32(r_VTOR, (void*) Vector_Table);
}

void Set_ISR (void (**IVT)(void), enum IRQ_Bits IRQ, void (*ISR)(void))
{
	IVT[16 + IRQ] = ISR;
}

void Set_Interrupt_Priority (
		enum IRQ_Bits           IRQ_Bits,
		enum Interrupt_Priority Priority
) {
	const uint32_t r_NVIC_IPR_0 = 0xE000'E400;

	for (uint8_t i = 0; i < 31; ++i)
	{
		if (IRQ_Bits & (1 << i))
		{
			const uint8_t  IRQ_No = i % 4;
			const uint32_t IPR    = r_NVIC_IPR_0 + ((IRQ_No / 4) * 4);
			const uint8_t  Offset = IRQ_No * 8 + 6;

			/* Clear old priority bits, then write `Priority` in its place. */
			uint32_t New_IPR = (IPR & ~(3 << Offset)) | (Priority << Offset);
			Wr32(IPR, New_IPR);
		}
	}
}
