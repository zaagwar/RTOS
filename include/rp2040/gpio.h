#ifndef RP2040_GPIO_H
#define RP2040_GPIO_H

#include <rp2040/common.h>

enum Port_Bits : uint32_t
{
	Port_Bit_0  = (1 << 0),
	Port_Bit_1  = (1 << 1),
	Port_Bit_2  = (1 << 2),
	Port_Bit_3  = (1 << 3),
	Port_Bit_4  = (1 << 4),
	Port_Bit_5  = (1 << 5),
	Port_Bit_6  = (1 << 6),
	Port_Bit_7  = (1 << 7),
	Port_Bit_8  = (1 << 8),
	Port_Bit_9  = (1 << 9),
	Port_Bit_10 = (1 << 10),
	Port_Bit_11 = (1 << 11),
	Port_Bit_12 = (1 << 12),
	Port_Bit_13 = (1 << 13),
	Port_Bit_14 = (1 << 14),
	Port_Bit_15 = (1 << 15),
	Port_Bit_16 = (1 << 16),
	Port_Bit_17 = (1 << 17),
	Port_Bit_18 = (1 << 18),
	Port_Bit_19 = (1 << 19),
	Port_Bit_20 = (1 << 20),
	Port_Bit_21 = (1 << 21),
	Port_Bit_22 = (1 << 22),
	Port_Bit_23 = (1 << 23),
	Port_Bit_24 = (1 << 24),
	Port_Bit_25 = (1 << 25),
	Port_Bit_26 = (1 << 26),
	Port_Bit_27 = (1 << 27),
	Port_Bit_28 = (1 << 28),
	Port_Bit_29 = (1 << 29),
};

enum Port : uint8_t
{
	Port_0 = 0,
	Port_1,
	Port_2,
	Port_3,
	Port_4,
	Port_5,
	Port_6,
	Port_7,
	Port_8,
	Port_9,
	Port_10,
	Port_11,
	Port_12,
	Port_13,
	Port_14,
	Port_15,
	Port_16,
	Port_17,
	Port_18,
	Port_19,
	Port_20,
	Port_21,
	Port_22,
	Port_23,
	Port_24,
	Port_25,
	Port_26,
	Port_27,
	Port_28,
	Port_29
};

enum Port_Function : uint8_t
{
	Port_Function_SPI = 1,
	Port_Function_UART,
	Port_Function_I2C,
	Port_Function_PWM,
	Port_Function_SIO,
	Port_Function_PIO_0,
	Port_Function_PIO_1,
	Port_Function_Clock_GP_Out
};

enum Port_Output : uint32_t
{
	Port_Output      = 0xD000'0010,
	Port_Output_High = 0xD000'0014,
	Port_Output_Low  = 0xD000'0018,
	Port_Flip_Output = 0xD000'001C
};

enum Port_Output_Enable : uint32_t
{
	Port_OE               = 0xD000'0020,
	Port_Direction_Output = 0xD000'0024,
	Port_Direction_Input  = 0xD000'0028,
	Port_Flip_Direction   = 0xD000'002C
};

/* Set the function of a single port. */
void GPIO_Select_Port_Function
(
	enum Port Port,
	enum Port_Function Which
);

/* Set the direction/output of one or more ports. */
void GPIO_Enable_Ports
(
	enum Port_Bits Ports,
	enum Port_Output_Enable Which
);

void GPIO_Drive_Ports
(
	enum Port_Bits Ports,
	enum Port_Output Which
);

/* Set the direction/output of a single port. */
void GPIO_Enable_Port
(
	enum Port Port,
	enum Port_Output_Enable Which
);

void GPIO_Drive_Port
(
	enum Port Port,
	enum Port_Output Which
);

/* Read the input/output value of a single port. */
bool GPIO_Read_Output (enum Port Port);
bool GPIO_Read_Input (enum Port Port);

#endif /* RP2040_GPIO_H */
