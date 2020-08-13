/* decode.h
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

#ifndef _DECODE_H_
#define _DECODE_H_

#include <sys/types.h>
#include <stdint.h>

char * decode(uint16_t opcode, uint32_t cur_PC, unsigned char *file, uint32_t size, uint32_t start_address);

#endif
