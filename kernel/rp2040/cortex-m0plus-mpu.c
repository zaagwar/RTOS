#include <rp2040/cortex-m0plus-mpu.h>

void Start_MPU (void)
{
	const uint32_t r_MPU_Control = 0xE000'ED94;

	/* Enable the MPU. */
	Wr8(r_MPU_Control, 1);

	/* Use the MPU when in HardFault and NMI handlers. */
	Wr8(r_MPU_Control, 3);
}

bool MPU_Protect_Region
(
	const enum Region Region,
	const uint32_t    Region_Start_Address,
	const uint8_t     Region_Size,
	const bool        Execute_Never,
	const enum Access_Permission Privileged_Access_Permission,
	const enum Access_Permission Unprivileged_Access_Permission
) {
	const uint32_t r_MPU_RASR = 0xE000'EDA0;
	const uint32_t r_MPU_RBAR = 0xE000'ED9C;

	uint32_t Access_Permissions;

	/* Neither privileged nor unprivileged code may read or write here. */
	if ( Privileged_Access_Permission == No_Access )
		Access_Permissions = 0b000;

	else if ( Privileged_Access_Permission == Full_Access )
	{
		/* Privileged code can both read and write to this memory region, but
		 * unprivileged code cannot access this memory at all.
		 */
		if ( Unprivileged_Access_Permission == No_Access )
			Access_Permissions = 0b001;

		/* Privileged code can read and write, but unprivileged code may only
		 * read from this memory.
		 */
		else if ( Unprivileged_Access_Permission == Read_Only )
			Access_Permissions = 0b010;

		/* Both privileged and unprivileged code may both read and write to and
		 * from this memory region. */
		else if ( Unprivileged_Access_Permission == Full_Access )
			Access_Permissions = 0b011;

		else return false;
	}

	else if ( Privileged_Access_Permission == Read_Only )
	{
		/* Privileged code can only read this memory, but unprivileged code
		 * cannot access this memory.
		 */
		if ( Unprivileged_Access_Permission == No_Access )
			Access_Permissions = 0b101;

		/* Both privileged and unprivileged code may only read this memory. */
		else if ( Unprivileged_Access_Permission == Read_Only )
			Access_Permissions = 0b110;

		else return false;
	}

	else return false;

	/* Specify the start address and region number of the memory to protect. */
	const uint8_t Valid = 1 << 4;
	Wr32(r_MPU_RBAR, (Region_Start_Address & 0xFFFF'FF00) | Valid | Region);

	/* Enable the region with the given attributes and size. */
	Wr32
	(
		r_MPU_RASR,
		(Execute_Never << 28) | (Access_Permissions << 24)
		| (Region_Size << 1) | 1
	);

	return true;
}
