ENTRY(Init)

MEMORY
{
	FLASH (RWX) : ORIGIN = 0x10000000, LENGTH = 16M
	SRAM  (RWX) : ORIGIN = 0x20000000, LENGTH = 264K
}

REGION_ALIAS("BOOT_LMA_REGION", FLASH);
REGION_ALIAS("TEXT_LMA_REGION", FLASH);
REGION_ALIAS("BSS_LMA_REGION",  FLASH);

SECTIONS
{
	/* The boot section contains the first code that is run by the CPU after
	 * its power-on reset. Before running this code, the CPU computes its CRC-32
	 * checksum and compares it against the last four bytes of this section. If
	 * the checksums match, the code is run by the CPU. Otherwise, the CPU halts
	 * and nothing runs.
	 */
	.Boot :
	{
		__Boot_Start = .;
	
		KEEP(*(.boot))
	
		__Boot_Stop = .;
	} > BOOT_LMA_REGION

	/* Before running any code in the boot section, the CPU will read the first
	 * 252 bytes from flash and calculate its CRC-32 checksum. Then it will
	 * compare that checksum to the final four bytes, which should contain the
	 * same checksum. If the checksums match, the code will run. Otherwise, the
	 * CPU halts and nothing runs.
	 * It is extremely important that this section is exactly 256 bytes in size
	 * and that the final four bytes of this section contain the CRC-32 checksum
	 * of the first 252 bytes.
	 */
	ASSERT(__Boot_Stop - __Boot_Start == 256, "Invalid .boot2 size")

	/* The text section contains all of the kernel's code. After the bootloader
	 * in the boot section loads this section into RAM, it jumps to the very
	 * beginning of this section, which should be the address of `Init`.
	 */
	. = 0x20000100;
	.Text : AT(0x10000100)
	{
		__Text_Start = .;

		*(.text. .text.Init)
		KEEP(*(.text .text.*))
		
		__Text_Stop = .;
	}
	ASSERT(__Text_Stop - __Text_Start < 8192, ".Text too small!")

	. = 0x20010000;
	.Data BLOCK(4) : AT(0x10010000)
	{
		__Data_Start = .;
	
		*(.data .data.*)
		*(.rodata .rodata.*)
	
		__Data_Stop = .;
	}
	ASSERT(__Data_Stop - __Data_Start < 4096, ".Data too small!")

	. = 0x20030000;
	.BSS BLOCK(4) : AT(0x10030000)
	{
		__BSS_Start = .;

		KEEP(*(.bss))

		__BSS_Stop = .;
	}
	ASSERT(__BSS_Stop - __BSS_Start < 4096, ".BSS too small!")
}

/* Export these symbols so they can be used in source code. */
PROVIDE(__Boot_Start = __Boot_Start);
PROVIDE(__Boot_Stop  = __Boot_Stop);
PROVIDE(__Text_Start = __Text_Start);
PROVIDE(__Text_Stop  = __Text_Stop);
PROVIDE(__Data_Start = __Data_Start);
PROVIDE(__Data_Stop  = __Data_Stop);
PROVIDE(__BSS_Start  = __BSS_Start);
PROVIDE(__BSS_Stop   = __BSS_Stop);
