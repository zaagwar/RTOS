#ifndef RP2040_SMP_H
#define RP2040_SMP_H

#include <rp2040/common.h>

enum Core : uint8_t
{
	Core_0 = 0,
	Core_1,
	n_Cores
};

/* This is not necessarily meant to keep track of how many cores are online,
 * though it can be used to do so, but to track which cores are online. As such,
 * it should not be interpreted as an integer value, but as a bitmap where a
 * given bit is set if the corresponding core is online. The least significant
 * bit here represents core zero.
 */
extern uint8_t Active_Cores;

/* An array of natural numbers each representing the amount of time that has
 * elapsed since the core has been reset.
 */
extern uint32_t Core_Uptimes[2];

/* Assuming a dual-core processor, whichever core calls this function will
 * power-on the other core.
 */
void Start_Other_Core
(
	void (**Vector_Table)(void),
	void (*Entry)(void),
	uintptr_t Stack
);

#endif /* RP2040_SMP_H */
