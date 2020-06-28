/* dcdis definitions
 *
 * Copyright (C) 1999 Lars Olsson
 *
 * This file is part of dcdis.
 *
 * dcdis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef _DCDIS_H_
#define _DCDIS_H_

#include <sys/types.h>
#include <stdint.h>

#define N_O_BITS 16	/* SH-4 instructions are 16-bit fixed width */
#define START_ADDRESS	0x8c010000

/* Only include symbol stuff if needed functions are available */
#if defined (HAVE_STRSTR) && defined(HAVE_MEMCPY)
#define DO_SYMBOL 1
#endif

uint16_t char2short(uint8_t *);
uint32_t char2int(uint8_t *);
char isAlpha(char);
void usage(void);

#endif
