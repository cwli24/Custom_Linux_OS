/* types.h - Defines to use the familiar explicitly-sized types in this
 * OS (uint32_t, int8_t, etc.).  This is necessary because we don't want
 * to include <stdint.h> when building this OS
 * vim:ts=4 noexpandtab
 */

#ifndef _TYPES_H
#define _TYPES_H

#define NULL            0
#define FOUR_MB         0x400000
#define FOUR_KB         0x1000
#define KEY_BUF_SIZE    129             // The size of the read buffer for the keyboard
#define MAX_TERM_NUM    3               // The number of terminals we support
#define MAX_PROCESSES   6               // The number of processes we can run
#define HIST_COM_NUM    10              // The number of commands to keep in the history buffer

#ifndef ASM

/* Types defined here just like in <stdint.h> */
typedef int int32_t;
typedef unsigned int uint32_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef char int8_t;
typedef unsigned char uint8_t;

typedef enum { false, true } bool;

#endif /* ASM */

#endif /* _TYPES_H */
