/* dcdis.c - very simple Dreamcast(tm) disassembler
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

#include <sys/types.h>
#include "dcdis.h"
#include "decode.h"
#ifdef DO_SYMBOL
#include "symtab.h"
#endif
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef DO_SYMBOL
extern unsigned char SYMTAB;
#endif

int standard_disp = 0;

uint16_t
char2short(unsigned char *buf)
{

	uint16_t val = 0;
	int i;

	for (i = 1; i >= 0; i--) {
		val = val<<8;
		val |= buf[i];
	}
	return (val);

}

uint32_t
char2int(unsigned char *buf)
{

	uint32_t val = 0;
	int i;

	for (i = 3; i>= 0; i--)
	{
		val = val<<8;
		val |= buf[i];
	}
	return (val);

}

char
isAlpha(char c)
{

	if (c >= ' ' && c < 127)
	{
		return(c);
	}
	return ('.');

}

void
usage()
{

	fprintf(stdout, "dcdis 0.5a (10-Dec-2019)\n");
	fprintf(stdout, "usage: dcdis [options] filename\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, " -b<address>	binary file, text start\n");
	fprintf(stdout, " -o<filename>	file to write output to (default: stdout)\n");
#ifdef DO_SYMBOL
	fprintf(stdout, " -s<filename>	Katana MAP file\n");
#endif
	fprintf(stdout, " -d		standard displacement\n");
	fprintf(stdout, " filename	file to disassemble\n");
	exit(0);

}

int
main(int argc, char **argv)
{

	uint16_t my_opcode;
	char *fname1 = NULL;
	FILE *s1 = NULL, *out;
#ifdef DO_SYMBOL
	FILE *sym;
	char *my_sym;
#endif
	int i, j;
	struct stat stat_buf;
	unsigned char *file = NULL;

	uint32_t my_pc;
	uint32_t start_address = START_ADDRESS;

	out = stdout;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'b':
#ifdef HAVE_SSCANF
					if (sscanf(&argv[i][2], "%x", &start_address) == 0) {
						usage();
					}
#else
					fprintf(stderr, "Can't interpret text address on this system...using default 0x%x\n", START_ADDRESS);
#endif
					break;
				case 'o':
					if ((out = fopen(&argv[i][2], "w")) == NULL) {
						perror("dcdis: open file");
						exit(0);
					}
					break;
#ifdef DO_SYMBOL
				case 's':
					SYMTAB = 1;
					if ((sym = fopen(&argv[i][2], "r")) == NULL) {
						perror("dcdis: symbol table file");
						exit (0);
					}

					if (symtab_read(sym) == -1) {
						perror("dcdis: symbol table file");
						exit (0);
					}
					break;
#endif

				case 'd':
					standard_disp = 1;
					break;

				default:
					usage();
					break;
			}
		} else {
			fname1 = argv[i];
			if ((s1 = fopen(fname1, "r")) == NULL) {
				perror("dcdis: open file");
				exit(0);
			}

	 		if (stat(argv[i], &stat_buf) != 0) {
				 perror("dcdis: stat()");
				 exit(-1);
			 }

			 if (!(file = (unsigned char *)calloc(1, stat_buf.st_size))) {
				 fprintf(stderr, "dcdis: File is too large!");
				 exit(-1);
			 }
		}
	}

	if (s1 == NULL) {
		usage();
	}

	fprintf(stdout, "Dreamcast(tm) Disassembler v0.5a\n");
	fprintf(stdout, "Coded by Maiwe in 1999-2004\n");
	fprintf(stdout, "Updated by Moopthehedgehog in 2019\n");

	my_pc = start_address;

	if (fread(file, stat_buf.st_size, 1, s1) == 0) {
		perror("dcdis: fread()");
		exit (-1);
	}

	fprintf(out, "\n");
	for (i = 0; i < stat_buf.st_size; i += N_O_BITS/8) {
#ifdef DO_SYMBOL
		if ((my_sym = (char *)symtab_lookup(my_pc)) != NULL) {
			fprintf(out, "%s:\n", my_sym);
		}
#endif
		fprintf(out, "H'%08x: ", my_pc);

		my_opcode = char2short(&file[i]);
		fprintf(out, "H'%04x  ", my_opcode);

		for (j = 0; j < (N_O_BITS/8); j++) {
			fprintf(out, "%c", isAlpha(file[i+j]));
		}

		fprintf(out, "  %s\n", decode(my_opcode, my_pc, file, stat_buf.st_size, start_address));
		my_pc += N_O_BITS/8;
	}
	return (0);

}
