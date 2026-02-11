#ifndef RP2040_REGULATOR_H
#define RP2040_REGULATOR_H

#include <rp2040/common.h>

enum Regulator_Voltage : uint8_t
{
	Voltage_0_80 = 0b0000, /* 0.80 volts */
	Voltage_0_85 = 0b0110, /* 0.85 volts */
	Voltage_0_90 = 0b0111, /* 0.90 volts */
	Voltage_0_95 = 0b1000, /* 0.95 volts */
	Voltage_1_00 = 0b1001, /* 1.00 volts */
	Voltage_1_05 = 0b1010, /* 1.05 volts */
	Voltage_1_10 = 0b1011, /* 1.10 volts (Default) */
	Voltage_1_15 = 0b1100, /* 1.15 volts */
	Voltage_1_20 = 0b1101, /* 1.20 volts */
	Voltage_1_25 = 0b1110, /* 1.25 volts */
	Voltage_1_30 = 0b1111, /* 1.30 volts */
};

void Set_Regulator_Voltage (enum Regulator_Voltage Regulator_Voltage);
void Disable_Voltage_Regulator (void);

#endif /* RP2040_REGULATOR_H */
