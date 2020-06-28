/* decode.h
 *
 * Copyright (C) 1999 Lars Olsson
 *
 * This file is part of dcdis.
 *
 * dcdis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef _DECODE_H_
#define _DECODE_H_

#include <sys/types.h>
#include <stdint.h>

//char *decode(uint16_t, uint32_t, char *, uint32_t, uint32_t);

char *decode(uint32_t, uint16_t (*)(uint32_t address, void *private_data), void*);


#endif
