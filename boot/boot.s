;@ See rp2040 datasheet section 2.8.3. "Bootrom Contents"

.section .boot, "ax" @progbits

entry:
	;@ Connect the SSI to the QSPI pads after restoring
	;@ all QSPI pad controls to their default state.
	ldrh r1, =0x4649 ;@ IF, `_connect_internal_flash`
	bl query
	blx r0

	;@ Configure SSI to generate the standard serial
	;@ read command (03h).
	ldrh r1, =0x5843 ;@ CX, `_flash_enter_cmd_xip`
	bl query
	blx r0

	;@ Load the first 8KiB of flash to the very bottom
	;@ of physical memory and ignore the XIP cache.
	ldrh r1, =0x3443 ;@ C4, `_memcpy44`
	bl query

	;@ Copy all code to the beginning of SRAM
	mov r3, r0          ;@ preserve the returned function
	ldr r0, =0x20000000 ;@ bottom of physical memory
	ldr r1, =0x13000100 ;@ bypass XIP cache completely
	ldr r2, =0x2000     ;@ 8192 bytes (8 KiB)
	blx r3

	;@ Hand off execution to the kernel.
	add r0, #1
	bx r0

query:
	push { lr }

	;@ Assume that r1 was given a two-byte code.
	mov r0, #0x14
	ldrh r2, [r0, #4] ;@ load pointer to helper function
	ldrh r0, [r0]     ;@ load pointer to function table

	;@ Call the lookup function.
	blx r2

	pop { pc }
