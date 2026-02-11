#include <rp2040/smp.h>
#include <rp2040/mailbox.h>

/* This is not necessarily meant to keep track of how many cores are online,
 * though it can be used to do so, but to track which cores are online. As such,
 * it should not be interpreted as an integer value, but as a bitmap where a
 * given bit is set if the corresponding core is online. The least significant
 * bit here represents core zero.
 * Core zero is always initially on, so this variable is initialized to one to
 * reflect that.
 */
uint8_t Active_Cores = 0b0000'0001;

/* An array of natural numbers each representing the amount of time that has
 * elapsed since the core has been reset.
 */
uint32_t Core_Uptimes[2];

void Start_Other_Core
(
	void (**Vector_Table)(void),
	void (*Entry)(void),
	uintptr_t Stack
) {
	const uint32_t Lockstep_Sequence[6] =
	{
		0, 0, 1,
		(uintptr_t) Vector_Table,
		(uintptr_t) Stack,
		(uintptr_t) Entry
	};

	uint32_t Sequence = 0;
	do
	{
		uint32_t Command = Lockstep_Sequence[Sequence];
		if ( !Command )
		{
			while ( !Mailbox_Is_Empty() )
				(void) Read_From_Mailbox();

			_ARMv6M_SEV;
		}

		Write_To_Mailbox(Command);
		_ARMv6M_SEV;

		while ( Mailbox_Is_Empty() );
		uint32_t Response = Read_From_Mailbox();

		if ( Response == Command ) ++Sequence;
		else Sequence = 0;
	} while ( Sequence < 6 );

	/* Update core tracker. */
	Wr8(&Active_Cores, 0b0000'0011);
}
