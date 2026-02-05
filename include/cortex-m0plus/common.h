#ifndef CORTEX_M0PLUS_COMMON_H
#define CORTEX_M0PLUS_COMMON_H

#include <common.h>

/* The Supervisor Call instruction generates a call to a system supervisor.
 * When the exception is escalated, a HardFault exception is caused. Use it as a
 * call to an operating system to provide a service.
 * Note that in older versions of the ARM architecture, SVC was called SWI,
 * Software Interrupt.
 */
/* Cycle count depends on processor and debug configuration. */
#define _ARMv6M_SVC(imm) __asm__ volatile ("svc #%0" :: "r" (imm))

/* The CPSIE and CPSID instructions are equivalent to using an MSR instruction:
 *   • the CPSIE i instruction is equivalent to writing a 0 into PRIMASK.PM.
 *   • the CPSID i instruction is equivalent to writing a 1 into PRIMASK.PM.
 */

/* Disable interrupt. This sets PRIMASK.PM to 0.
 * `i` indicates that PRIMASK is affected. Raises the current priority to 0 when
 * set to 1. PRIMASK is a 1-bit register, accessible only from privileged
 * execution.
 */
/* Completes in one clock cycle. */
#define _ARMv6M_CPSID(i) __asm__ volatile ("cpsid #%0" :: "r" (i))

/* Enable interrupt. This sets PRIMASK.PM to 1.
 * `i` indicates that PRIMASK is affected. Raises the current priority to 0 when
 * set to 1. PRIMASK is a 1-bit register, accessible only from privileged
 * execution.
 */
/* Completes in one clock cycle. */
#define _ARMv6M_CPSIE(i) __asm__ volatile ("cpsie #%0" :: "r" (i))

/* Breakpoint causes a HardFault exception or a debug halt to occur depending on
 * the presence and configuration of the debug support.
 */
/* Cycle count depends on processor and debug configuration. */
#define _ARMv6M_BKPT(imm) __asm__ volatile ("bkpt #%0" :: "r" (imm))

/* ARMv6-M can support software-based synchronization to system events using the
 * SEV and WFE hint instructions.
 * Software can:
 *   • use the WFE instruction to indicate that it is able to suspend execution
 *     of a process or thread until an event occurs, permitting hardware to
 *     enter a low power state.
 *   • rely on a mechanism that is transparent to software and provides low
 *   　　latency wakeup.
 *
 * The Wait For Event mechanism relies on hardware and software working together
 * to achieve energy saving. For example, stalling execution of a processor
 * until a device or another processor has set a flag:
 *   • the hardware provides the mechanism to enter the Wait For Event low-power
 *     state.
 *   • software enters a polling loop to determine when the flag is set:
 *     — the polling processor issues a Wait For Event instruction as part of a
 *       polling loop if the flag is clear.
 *     — an event is generated (hardware interrupt or Send Event instruction
 *       from another processor) when the flag is set.
 *
 * The mechanism depends on the interaction of:
 *   • WFE wake up events
 *   • the Event Register
 *   • the Send Event instruction
 *   • the Wait For Event instruction
 */

/* Send Event is a hint instruction. It causes an event to be signaled to all
 * CPUs within a multiprocessor system. The mechanism used to signal the event
 * to the processors is implementation defined. The Send Event instruction
 * generates a wakeup event. The Send Event instruction is available to both
 * unprivileged and privileged code.
 */
/* Completes in one clock cycle. */
#define _ARMv6M_SEV __asm__ volatile ("sev")

/* The action of the Wait For Event instruction, depends on the state of the
 * Event Register:
 *   • If the Event Register is set, the instruction clears the register and
 *     returns immediately.
 *   • If the Event Register is clear the processor can suspend execution and
 *     enter a low-power state. It can remain in that state until the processor
 *     detects a WFE wakeup event or a reset. When the processor detects a WFE
 *     wakeup event, or earlier if the implementation chooses, the WFE
 *     instruction completes.
 * The Wait For Event instruction, WFE, is available to both unprivileged and
 * privileged code. WFE wakeup events can occur before a WFE instruction is
 * issued. Software using the Wait For Event mechanism must tolerate spurious
 * wake up events, including multiple wakeups.
 */
/* Completes in two clock cycles. */
#define _ARMv6M_WFE __asm__ volatile ("wfe")

/* Wait For Interrupt is a hint instruction that suspends execution until one
 * of a number of events occurs. When a processor issues a WFI instruction it
 * can suspend execution and enter a low-power state. It can remain in that
 * state until the processor detects one of the following WFI wake up events:
 *   • A reset.
 *   • An asynchronous exception at a priority that, if PRIMASK.PM was set to 0,
 *     would preempt any currently active exceptions.
 *     Note that if PRIMASK.PM is set to 1, an asynchronous exception that has a
 *     higher group priority than any active exception results in a WFI
 *     instruction exit. If the group priority of the exception is less than or
 *     equal to the execution group priority, the exception is ignored.
 *   • If debug is enabled, a debug event.
 *   • An IMPLEMENTATION DEFINED WFI wakeup event.
 *
 * The WFI instruction completes when the hardware detects a WFI wake up event,
 * or earlier if the implementation chooses.
 * 
 * The processor recognizes WFI wake up events only after issuing the WFI
 * instruction.
 * Note that because debug entry is one of the WFI wake up events,
 * ARM recommends that software uses Wait For Interrupt as part of an idle loop
 * rather than waiting for a single specific interrupt event to occur and then
 * moving forward. This ensures the intervention of debug while waiting does not
 * significantly change the operation of the program being debugged.
 *
 * A common implementation practice is to complete any entry into powerdown
 * routines with a WFI instruction. Typically, the WFI instruction:
 *   1. Forces the suspension of execution, and of all associated bus activity.
 *   2. Ceases to execute instructions from the processor.
 * The control logic required to do this typically tracks the activity of the
 * bus interfaces of the processor. This means it can signal to an external
 * power controller that there is no ongoing bus activity. The exact nature of
 * this interface is IMPLEMENTATION DEFINED, but the use of Wait For Interrupt
 * as the only architecturally-defined mechanism that completely suspends
 * execution makes it very suitable as the preferred powerdown entry mechanism.
 */
/* Completes in two clock cycles. */
#define _ARMv6M_WFI __asm__ volatile ("wfi")

/* YIELD is a hint instruction. It enables software with a multithreading
 * capability to indicate to the hardware that it is performing a task, for
 * example a spinlock, that could be swapped out to improve overall system
 * performance. Hardware can use this hint to suspend and resume multiple code
 * threads if it supports the capability.
 */
/* Completes in one clock cycle. */
#define _ARMv6M_YIELD __asm__ volatile ("yield")

/* No Operation does nothing. This instruction can be used for code alignment
 * purposes. The timing effects of including a NOP instruction in code are not
 * guaranteed. It can increase execution time, leave it unchanged, or even
 * reduce it. NOP instructions are therefore not suitable for timing loops.
 */
#define _ARMv6M_NOP __asm__ volatile ("nop")

/* Memory barrier is the general term applied to an instruction, or sequence of
 * instructions, used to force synchronization events by a processor with
 * respect to retiring load or store instructions. A memory barrier is used to
 * guarantee completion of preceding load or store instructions to the
 * programmers' model, flushing of any prefetched instructions prior to the
 * event, or both. ARMv6-M includes three explicit barrier instructions to
 * support the memory order model.
 *   • DMB
 *   • DSB
 *   • ISB
 *
 * Memory barriers affect explicit reads and writes to the memory system
 * generated by load and store instructions being executed in the processor.
 * Reads and writes generated by DMA transactions and instruction fetches are
 * not explicit accesses.
 */

/* The ISB instruction flushes the pipeline in the processor, so that all
 * instructions following the pipeline flush are fetched from memory after the
 * instruction has been completed. It ensures that the effects of context
 * altering operations, such as branch predictor maintenance operations, in
 * addition to all changes to the special-purpose registers where applicable,
 * executed before the ISB instruction are visible to the instructions fetched
 * after the ISB.
 *
 * In addition, the ISB instruction ensures that any branches that appear in
 * program order after the ISB are always written into the branch prediction
 * logic with the context that is visible after the ISB. This is required to
 * ensure correct execution of the instruction stream.
 *
 * Any context altering operations appearing in program order after the ISB only
 * take effect after the ISB has been executed. This is because of the behavior
 * of the context altering instructions.
 *
 * ARM implementations are free to choose how far ahead of the current point of
 * execution they prefetch instructions; either a fixed or a dynamically varying
 * number of instructions. In addition to being free to choose how many
 * instructions to prefetch, an ARM implementation can choose the possible
 * future execution path to prefetch along. For example, after a branch
 * instruction, it can choose to prefetch either the instruction following the
 * branch or the instruction at the branch target. This is known as branch
 * prediction.
 *
 * A potential problem with all forms of instruction prefetching is that the
 * instruction in memory can be changed after it was prefetched but before it is
 * executed. If this happens, the modification to the instruction in memory
 * does not normally prevent the already prefetched copy of the instruction from
 * executing to completion. Use the ISB and memory barrier instructions, DMB or
 * DSB as appropriate, to force execution ordering where necessary.
 */
/* Completes in three clock cycles. */
#define _ARMv6M_ISB __asm__ volatile ("isb")

/* The DMB instruction is a data memory barrier. DMB exhibits the following
 * behavior:
 *   • All explicit memory accesses by instructions occurring in program order
 *     before this instruction are globally observed before any explicit memory
 *     accesses because of instructions occurring in program order after this
 *     instruction are observed.
 *   • The DMB instruction has no effect on the ordering of other instructions
 *     executing on the processor.
 * As such, DMB ensures the apparent order of the explicit memory operations
 * before and after the instruction, without ensuring their completion
 */
/* Completes in three clock cycles. */
#define _ARMv6M_DMB __asm__ volatile ("dmb")

/* The DSB instruction operation acts as a special kind of DMB.
 * The DSB operation completes when all explicit memory accesses before this
 * instruction complete. In addition, no instruction subsequent to the DSB can
 * execute until the DSB completes. This instruction completes only when both:
 *   • any explicit memory access made before this instruction is complete.
 *   • all cache and branch predictor maintenance operations before this
 *     instruction complete.
 */
/* Completes in three clock cycles. */
#define _ARMv6M_DSB __asm__ volatile ("dsb")

/* Read the CPU ID Base Register to determine: the ID number of the processor
 * core, the version number of the processor core, the implementation details of
 * the processor core.
 */
uint32_t CPUID (void);

/* Returns zero when read from processor core zero, and one when read from
 * processor core one.
 */
bool Who_Am_I (void);

#endif /* CORTEX_M0PLUS_COMMON_H */
