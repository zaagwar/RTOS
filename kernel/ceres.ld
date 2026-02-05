ENTRY(start_kernel)

MEMORY
{
	FLASH (RWX) : ORIGIN = 0x10000000, LENGTH = 16M
	SRAM  (RWX) : ORIGIN = 0x20000000, LENGTH = 264K
}

REGION_ALIAS("BOOT_REGION", FLASH);
REGION_ALIAS("TEXT_REGION", FLASH);
REGION_ALIAS("DATA_REGION", FLASH);

SECTIONS
{
	/* The boot section contains the first code that is run by the CPU after
	 * its power-on reset. Before running this code, the CPU computes its CRC-32
	 * checksum and compares it against the last four bytes of this section. If
	 * the checksums match, the code is run by the CPU. Otherwise, the CPU halts
	 * and nothing runs.
	 */
	.boot :
	{
		__boot_start = .;
	
		KEEP(*(.boot))
	
		__boot_stop = .;
	} > BOOT_REGION

	/* Before running any code in the boot section, the CPU will read the first
	 * 252 bytes from flash and calculate its CRC-32 checksum. Then it will
	 * compare that checksum to the final four bytes, which should contain the
	 * same checksum. If the checksums match, the code will run. Otherwise, the
	 * CPU halts and nothing runs.
	 * It is extremely important that this section is exactly 256 bytes in size
	 * and that the final four bytes of this section contain the CRC-32 checksum
	 * of the first 252 bytes.
	 */
	ASSERT(__boot_stop - __boot_start == 256, "Invalid .boot2 size")

	/* The text section contains all of the kernel's code. After the bootloader
	 * in the boot section loads this section into RAM, it jumps to the very
	 * beginning of this section, which should be the address of `Main_Core_0`.
	 */
	.text :
	{
		__text_start = .;

		*(.text. .text.start_kernel)
		KEEP(*(.text .text.*))
		
		__text_stop = .;
	} > TEXT_REGION

	.data :
	{
		__data_start = .;
	
		*(.data .data.*)
		*(.rodata .rodata.*)
	
		__data_stop = .;
	} > DATA_REGION

	/* The bootloader only loads 8 KiB (8192 B) of memory from flash to RAM.
	 * As the amount of kernel code and data grows, I will surely exceed this
	 * limit and be forced to increase this number. If too little data is moved
	 * into RAM, subtle bugs may appear that would be very tricky to spot, so
	 * it is important to have this check in place.
	 */
	ASSERT(__data_stop - __text_start < 8192, "Image is too large")
}

/* Export these symbols so they can be used in source code. */
PROVIDE(__boot_start = __boot_start);
PROVIDE(__boot_stop  = __boot_stop);
PROVIDE(__text_start = __text_start);
PROVIDE(__text_stop  = __text_stop);
PROVIDE(__data_start = __data_start);
PROVIDE(__data_stop  = __data_stop);
