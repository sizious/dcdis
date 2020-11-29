/**
 * Katana MAP file interpreter
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

#include <sys/types.h>
#include "symtab.h"
#include "dcdis.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

unsigned char SYMTAB = 0;	/* Default is to not use symbol table */

struct symtab *my_sym_tab[TABLE_SIZE];

void
symtab_insert(struct symtab *entry)
{

	uint32_t index = entry->addr;

	index = index % TABLE_SIZE;
	
	entry->next = NULL;
	if (my_sym_tab[index] != NULL) {
		entry->next = my_sym_tab[index];
	}
	my_sym_tab[index] = entry;

}

void
symtab_read_line(FILE *fp, char *buf, uint32_t size)
{

	unsigned int i;

	for (i = 0; i < size; i++) {
		if (fread(buf+i, 1, 1, fp) == 0) {
			halt("error in MAP file!\n");
		}
		if (buf[i] == '\n') {
			break;
		}
	}

}

void
symtab_read_page(FILE *fp)
{

	char buf[256];

	memset(&buf, 0, sizeof(buf));

	while(1) {
		symtab_read_line(fp, buf, sizeof(buf));
		if ((char *)strstr((char *)buf, "LINKAGE EDITOR EXTERNALLY DEFINED SYMBOLS LIST") != NULL) {
			break;
		}
	}

	while(1) {
		symtab_read_line(fp, buf, sizeof(buf));
		if ((char *)strstr((char *)buf, "SYMBOL NAME") != NULL) {
			break;
		}
	}
	symtab_read_line(fp, buf, sizeof(buf));

}

void
symtab_read(FILE *fp)
{

	char buf[256];
	char buf2[256];
	char *ptr;
	struct symtab *entry;
	int i;

	symtab_read_line(fp, buf, sizeof(buf));

	/* Every MAP file begins with something like this */
	if ((char *)strstr(buf, "H SERIES LINKAGE EDITOR") == NULL) {
		halt("Not a Katana MAP file!\n");
	}

	/* Ignore everything but external symbols for now */
	symtab_read_page(fp);

	while(1) {
		memset(&buf, 0, sizeof(buf));
		memset(&buf2, 0, sizeof(buf2));

		if (fread(buf, 1, 1, fp) == 0) {
			break;				// We're finished
		}
		if (buf[0] == PAGE_START) {
			symtab_read_page(fp);
		} else {
			
			if (!(entry = (struct symtab *)calloc(1, sizeof(struct symtab)))) {
				halt("Out of memory when storing symbol entries\n");
			}

			symtab_read_line(fp, buf+1, sizeof(buf)-1);
			for (i = 0; buf[i] != ' ' && buf[i] != '\n' && buf[i] != 0; i++);
			memcpy(buf2, buf, i);
			buf2[i] = 0;
			
			entry->symbol = (char *)strdup(buf2);
			
			if (buf[i] == '\n' || buf[i] == 0) {
				symtab_read_line(fp, buf, sizeof(buf));
			}
			if ((ptr = (char *)strstr(buf, "H'")) == NULL) {
				halt("error in MAP file!\n");
			}
			if (sscanf((ptr+2), "%x", &(entry->addr)) == 0) {
				halt("error in MAP file!\n");
			}

			symtab_insert(entry);
		}
	}

#ifdef DEBUG
	symtab_dump();
#endif	

}

char *
symtab_lookup(uint32_t addr)
{

	struct symtab *cur;
	int index = addr % TABLE_SIZE;

	if (SYMTAB != 0) {
		for (cur = my_sym_tab[index]; cur != NULL; cur = cur->next) {
			if (addr == cur->addr) {
				return (cur->symbol);
			}
		}
	}
	return (NULL);

}

void
symtab_free() {
	
	int index;
	struct symtab *cur;
	struct symtab *next;

	if (SYMTAB != 0) {
		for(index = 0; index < TABLE_SIZE; index++) {
			cur = my_sym_tab[index];
			while (cur != NULL) {				
				next = cur->next;

				free(cur->symbol);
				cur->symbol = NULL;

				free(cur);
				cur = next;
			}
			my_sym_tab[index] = NULL;
		}
	}

}

#ifdef DEBUG
void
symtab_dump() {

	int index;
	struct symtab *cur;

	if (SYMTAB != 0) {
		for(index = 0; index < TABLE_SIZE; index++) {
			for (cur = my_sym_tab[index]; cur != NULL; cur = cur->next) {				
				printf("%p: %d: 0x%x | %s\n", cur, index, cur->addr, cur->symbol);
			}									
		}
	}

}
#endif
