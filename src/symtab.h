/* symtab.h - Katana MAP file interpreter
 *
 * Copyright (C) 1999 Lars Olsson
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

void symtab_insert(struct symtab *);
void symtab_read_line(FILE *, char *, uint32_t);
void symtab_read_page(FILE *);
int symtab_read(FILE *);
char *symtab_lookup(uint32_t addr);

#endif
