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

unsigned char SYMTAB = 0;	/* Default is to not use symbol table */

struct symtab *my_sym_tab[TABLE_SIZE];

void
symtab_insert(struct symtab *entry)
{

	uint32_t index = entry->addr;

	index = index % TABLE_SIZE;

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
			fprintf(stderr, "error in MAP file!\n");
			exit (-1);
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

int
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
		fprintf(stderr, "Not a Katana MAP file!\n");
		exit (-1);
	}

	/* Ignore everything but external symbols for now */
	symtab_read_page(fp);

	while(1) {
		if (!(entry = (struct symtab *)calloc(1, sizeof(struct symtab *)))) {
			fprintf(stderr, "Out of memory?!\n");
			exit(-1);
		}

		if (fread(buf, 1, 1, fp) == 0) {
			break;				/* We're finished */
		}
		if (buf[0] == PAGE_START) {
			symtab_read_page(fp);
		} else {
			symtab_read_line(fp, buf+1, sizeof(buf)-1);
			for (i = 0; buf[i] != ' ' && buf[i] != '\n' && buf[i] != 0; i++);
			memcpy(buf2, buf, i);
			buf2[i] = 0;
			entry->symbol = (char *)strdup(buf2);
			if (buf[i] == '\n' || buf[i] == 0) {
				symtab_read_line(fp, buf, sizeof(buf));
			}
			if ((ptr = (char *)strstr(buf, "H'")) == NULL) {
				fprintf(stderr, "error in MAP file!\n");
				exit(-1);
			}
			if (sscanf((ptr+2), "%x", &(entry->addr)) == 0) {
				fprintf(stderr, "error in MAP file!\n");
				exit (-1);
			}
			symtab_insert(entry);
		}
	}
	// Guess we're done, return 0
	exit(0);
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
