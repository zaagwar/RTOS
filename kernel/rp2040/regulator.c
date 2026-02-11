#include <rp2040/regulator.h>

const uint32_t r_Regulator = 0x4006'4000;

void Set_Regulator_Voltage (enum Regulator_Voltage Regulator_Voltage)
{
	const uint16_t Regulator_OK_Bit = 1 << 12;
	const uint16_t Regulator_En_Bit = 1;

	/* Enable the regulator and set a custom internal voltage.
	 * Then, wait for the regulator to stabilize at the target voltage.
	 */
	Wr8(r_Regulator, (Regulator_Voltage << 4) | Regulator_En_Bit);
	while ( !(Rd16(r_Regulator) & Regulator_OK_Bit) );
}

void Disable_Voltage_Regulator (void)
{
	const uint8_t Regulator_En_Bit = 1;
	Wr8(r_Regulator | Atomic_Clear, Regulator_En_Bit);
}
