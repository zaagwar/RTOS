#include <rp2040/mailbox.h>

const uint32_t r_Mailbox_Status = 0xD000'0050;

bool Mailbox_Is_Empty (void)
{
	/* The LSB of this register indicates that our mailbox is full. */
	return !(Rd8(r_Mailbox_Status) & 1);
}

bool Mailbox_Is_Full (void)
{
	/* The second LSB indicates that our mailbox is currently full. */
	return !(Rd8(r_Mailbox_Status) & 2);
}

void Write_To_Mailbox (uint32_t Data)
{
	/* Write 32 bits to the other core's mailbox. */
	const uint32_t r_Mailbox_Write = 0xD000'0054;
	Wr32(r_Mailbox_Write, Data);
}

uint32_t Read_From_Mailbox (void)
{
	/* Read 32 bits from our mailbox and return the contents. */
	const uint32_t r_Mailbox_Read = 0xD000'0058;
	return Rd32(r_Mailbox_Read);
}
