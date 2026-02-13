#ifndef CERES_DISPATCH_H
#define CERES_DISPATCH_H

#include <ceres/common.h>
#include <ceres/scheduler.h>

/* When the primary core wants to switch contexts, this function is called. */
extern __attribute__ (( interrupt("IRQ") )) void Context_Switch_0 (void);

/* When the secondary core wants to switch contexts, this function is called. */
extern __attribute__ (( interrupt("IRQ") )) void Context_Switch_1 (void);

#endif /* CERES_DISPATCH_H */
