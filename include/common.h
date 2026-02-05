#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

/* LDR and STR instructions respectively. */
#define Rd32(Addr)        (*((volatile uint32_t*) (Addr)))
#define Wr32(Addr, value) (Rd32(Addr) = (uint32_t) (value))

/* LDRH and STRH instructions respectively. */
#define Rd16(Addr)        (*((volatile uint16_t*) (Addr)))
#define Wr16(Addr, value) (Rd16(Addr) = (uint16_t) (value))

/* LDRB and STRB instructions respectively. */
#define Rd8(Addr)        (*((volatile uint8_t*) (Addr)))
#define Wr8(Addr, value) (Rd8(Addr) = (uint8_t) (value))

#endif /* COMMON_H */
