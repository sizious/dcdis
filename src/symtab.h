/* symtab.h - Katana MAP file interpreter
 *
 * Copyright (C) 1999-2004 Lars Olsson
 * Copyright (C) 2019 Moopthehedgehog
 * Copyright (C) 2020 SiZiOUS
 *
 * This file is part of dcdis
 *
 * dcdis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <sys/types.h>
#include "dcdis.h"
#include <stdio.h>

#define TABLE_SIZE	4093	/* ought to be in the range */
#define PAGE_START	0x0c

struct symtab {
	uint32_t addr;
	char *symbol;
	struct symtab *next;
};

void symtab_insert(struct symtab *entry);
void symtab_read_line(FILE *fp, char *buf, uint32_t size);
void symtab_read_page(FILE *fp);
int symtab_read(FILE *fp);
char * symtab_lookup(uint32_t addr);

#endif
