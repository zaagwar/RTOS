#ifndef CORTEX_M0PLUS_MPU_H
#define CORTEX_M0PLUS_MPU_H

#include <cortex-m0plus/common.h>

enum Access_Permission : uint8_t
{
	No_Access = 0, /* Any access generates a permission fault */
	Read_Only,     /* Only read accesses are permitted */
	Full_Access    /* Both read and write accesses are permitted */
};

enum Region : uint8_t
{
	Region_0 = 0,
	Region_1,
	Region_2,
	Region_3,
	Region_4,
	Region_5,
	Region_6,
	Region_7,
};

void Start_MPU (void);

bool MPU_Protect_Region
(
	const enum Region Region,
	const uint32_t    Region_Start_Address,
	const uint8_t     Region_Size,
	const uint32_t    Region_Attributes,
	const enum Access_Permission Privileged_Access_Permission,
	const enum Access_Permission Unprivileged_Access_Permission
);

#endif /* CORTEX_M0PLUS_MPU_H */
