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

	ldrh r1, =0x3443 ;@ C4, `_memcpy44`
	bl query

	;@ Load 4 KiB of data from flash to SRAM bank three
	;@ and completely ignore the XIP cache.
	mov r3, r0          ;@ preserve the returned function
	ldr r0, =0x20010000 ;@ bottom of SRAM1
	ldr r1, =0x13010000 ;@ bypass XIP cache completely
	ldr r2, =0x1000     ;@ 4096 bytes (4 KiB)
	blx r3

	ldrh r1, =0x3443 ;@ C4, `_memcpy44`
	bl query

	;@ Load 4 KiB of static variables from flash to SRAM
	;@ bank three and completely ignore the XIP cache.
	mov r3, r0          ;@ preserve the returned function
	ldr r0, =0x20030000 ;@ bottom of SRAM3
	ldr r1, =0x13030000 ;@ bypass XIP cache completely
	ldr r2, =0x1000     ;@ 4096 bytes (4 KiB)
	blx r3

	ldrh r1, =0x3443 ;@ C4, `_memcpy44`
	bl query

	;@ Load 8 KiB of code to the very bottom of physical
	;@ memory and ignore the XIP cache.
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
