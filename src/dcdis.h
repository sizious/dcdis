/** 
 * dcdis definitions
 *
 * Copyright (C) 1999-2004 Lars Olsson (Maiwe)
 * Copyright (C) 2019 Moopthehedgehog
 * Copyright (C) 2020 SiZiOUS
 * 
 * This file is part of dcdis
 *
 * dcdis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _DCDIS_H_
#define _DCDIS_H_

#include <sys/types.h>
#include <stdint.h>

#define N_O_BITS 		16	/* SH-4 instructions are 16-bit fixed width */
#define N_O_BITS_BLOCK	N_O_BITS/8
#define START_ADDRESS	0x8c010000

/* Only include symbol stuff if needed functions are available */
#if defined (HAVE_STRSTR) && defined(HAVE_MEMCPY)
#define DO_SYMBOL 1
#endif

uint16_t char2short(unsigned char *buf);
uint32_t char2int(unsigned char *buf);
char is_alpha(char c);
void usage(void);

#endif // _DCDIS_H_
