#include <rp2040/cortex-m0plus.h>
#include <rp2040/cortex-m0plus-nvic.h>
#include <rp2040/cortex-m0plus-mpu.h>

uint32_t CPUID (void)
{
	const uint32_t r_CPUID = 0xE000'ED00;
	return Rd32(r_CPUID);
}

bool Who_Am_I (void)
{
	const uint32_t r_SIO_CPUID = 0xD000'0000;
	return !!Rd32(r_SIO_CPUID);
}
