#include <rp2040/gpio.h>

/* Set the function of a single port. */

void GPIO_Select_Port_Function
(
	enum Port Port,
	enum Port_Function Which
) {
	const uint32_t r_GPIO_Base = 0x4001'4000;
	Wr32((r_GPIO_Base + (8 * Port) + 4), Which & 0x0F);
}

/* Set the direction/output of one or more ports. */

void GPIO_Enable_Ports
(
	enum Port_Bits Ports,
	enum Port_Output_Enable Which
) {
	Wr32(Which, Ports);
}

void GPIO_Drive_Ports
(
	enum Port_Bits Ports,
	enum Port_Output Which
) {
	Wr32(Which, Ports);
}

/* Set the direction/output of a single port. */

void GPIO_Enable_Port
(
	enum Port Port,
	enum Port_Output_Enable Which
) {
	Wr32(Which, 1 << Port);
}

void GPIO_Drive_Port
(
	enum Port Port,
	enum Port_Output Which
) {
	Wr32(Which, 1 << Port);
}

/* Read the input/output value of a single port. */

bool GPIO_Read_Output (enum Port Port)
{
	const uint32_t r_GPIO_Out = 0x4001'4010;
	return !!(Rd32(r_GPIO_Out) & (1 << Port));
}

bool GPIO_Read_Input (enum Port Port)
{
	const uint32_t r_GPIO_In = 0x4001'4004;
	return !!(Rd32(r_GPIO_In) & (1 << Port));
}
