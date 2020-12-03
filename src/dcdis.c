/**
 * dcdis - a very simple Sega Dreamcast disassembler
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

#include "config.h"

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

#include "utils.h"
#include "vector.h"

#ifdef DO_SYMBOL
extern unsigned char SYMTAB;
#endif

int standard_disp = 0;

// Sega Dreamcast binary file to disassemble
char *g_filename_in = NULL;

// Binary buffer to disassemble
unsigned char *g_file_buffer = NULL;

// Plain text disassembled text
char *g_filename_out = NULL;

// command-line arguments not parsed by getopt
int g_real_argc = 0;
VECTOR_DECLARE(g_real_argv);

// options handled by dcdis
#define OPTIONS "b:dho:s:v"
char *g_parameterized_options;

// Input/output pointers
FILE *g_filein = NULL, *g_out = NULL;
int g_out_is_file = 0;

// Symbol table file (MAP file)
#ifdef DO_SYMBOL
FILE *g_sym;
#endif

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
is_alpha(char c)
{

	if (c >= ' ' && c < 127)
	{
		return(c);
	}
	return ('.');

}

void
app_finalize(void)
{
	
	program_name_finalize();

	VECTOR_FREE(g_real_argv);
	free(g_parameterized_options);
	
	if (g_file_buffer != NULL) {
		free(g_file_buffer);
	}

	if (g_filein != NULL) {
		fclose(g_filein);
	}

	if (g_out_is_file && g_out != NULL) {
		fclose(g_out);
	}

#ifdef DO_SYMBOL
	if (SYMTAB) {
		fclose(g_sym);
	}

	symtab_free();
#endif
	
}

void
app_initialize(char *argv0)
{
	
	// extract program name from command line
	program_name_initialize(argv0);

	// register cleanup function
	if (atexit(app_finalize)) {
		halt("unable to register atexit!\n");
	}

	// initialize the array for real argv values
	VECTOR_INIT(g_real_argv);

	// retrieve parameterized options
	g_parameterized_options = retrieve_parameterized_options(OPTIONS);

}
  
void
usage()
{

	fprintf(stdout, "Sega Dreamcast Disassembler (%s) v%s (%s)\n\n", PACKAGE_NAME, PACKAGE_VERSION, __DATE__);
	fprintf(stdout, "A very simple Sega Dreamcast disassembler.\n\n");
	fprintf(stdout, "Usage:\n");	
	fprintf(stdout, "\t%s [options] <filename>\n\n", program_name_get());
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "\t-b <address>  Set binary load address (default: 0x%x)\n", START_ADDRESS);
	fprintf(stdout, "\t-d            Use standard displacement\n");
    fprintf(stdout, "\t-h            Print usage information (you\'re looking at it)\n");	
	fprintf(stdout, "\t-o <filename> Write disassembly output to <filename> instead of stdout\n");
#ifdef DO_SYMBOL
	fprintf(stdout, "\t-s <filename> Use Katana MAP file\n");
#endif
	fprintf(stdout, "\t-v            Enable verbose mode\n");

}

void
parse_real_args(int argc, char *argv[])
{
	
	for(; optind < argc; optind++) {
		VECTOR_ADD(g_real_argv, argv[optind]);
	}

	g_real_argc = VECTOR_TOTAL(g_real_argv);

	if(g_real_argc > 0) {
		g_filename_in = VECTOR_GET(g_real_argv, char*, 0);
	}

}

int
main(int argc, char **argv)
{

	uint16_t my_opcode;

#ifdef DO_SYMBOL
	char *my_sym;
#endif

	int c, i, j;
	struct stat stat_buf;

	uint32_t my_pc;
	uint32_t start_address = START_ADDRESS;

	app_initialize(argv[0]);
	
	if (argc < 2) {
		usage();
		exit(EXIT_FAILURE);
	}
	
	g_out = stdout;
	
	// read the options
	opterr = 0; // suppress default getopt error messages
	while ((c = getopt(argc, argv, OPTIONS)) != -1) {
		switch (c) {
			case 'b':
#ifdef HAVE_SSCANF
				if (sscanf(optarg, "%x", &start_address) == 0) {
					halt("incorrect address: \"%s\"\n", optarg);
				}						
#else
				log_warn("can't set address on this system... using default 0x%x\n", START_ADDRESS);
#endif
				break;
			case 'd':				
				standard_disp = 1;
				break;
			case 'h':
				usage();
				exit(EXIT_SUCCESS);
				break;
			case 'o':
				g_out_is_file = 1;
				if ((g_out = fopen(optarg, "w")) == NULL) {
					halt("unable to open file: \"%s\"\n", optarg);					
				}
				break;
#ifdef DO_SYMBOL
			case 's':
				SYMTAB = 1;
				if ((g_sym = fopen(optarg, "r")) == NULL) {
					halt("unable to open symbol table file: \"%s\"\n", optarg);
				}
				symtab_read(g_sym);
				break;
#endif
			case 'v':
				verbose_enable();
				break;
			case '?':
				if (is_in_char_array(optopt, g_parameterized_options)) {
				  halt("option \"-%c\" requires an argument\n", optopt);
				} else if (isprint(optopt)) {
				  halt("unknown option \"-%c\"\n", optopt);
				} else {
				  halt("unknown option character \"\\x%x\"\n", optopt);
				}
			default:
				abort();
		}
	}

	// get extra arguments which are not parsed
	parse_real_args(argc, argv);	
	
	// we don't know how to deal with that  
	if (g_real_argc > 1) {
		halt("too many arguments\n");
	}

	// no arguments was passed...
	if (g_real_argc < 1) {    
		halt("too few arguments\n");
	}
	
	// check if the input file exists
	if (!is_file_exist(g_filename_in)) {
		halt("input file not found: \"%s\"\n", g_filename_in);
	}
  
	// check if the input file is ELF
	if (is_file_elf(g_filename_in)) {
		halt("elf format is unsupported, file must be raw binary\n");		
	}
	
	// open raw binary input file
	if ((g_filein = fopen(g_filename_in, "rb")) == NULL) {
		halt("unable to open file: \"%s\"\n", g_filename_in);
	}
	
	// retrieve stat info on the input file
	if (stat(g_filename_in, &stat_buf) != 0) {
		halt("unable to stat file: \"%s\"\n", g_filename_in);
	}

	// load input raw binary file in memory
	if (!(g_file_buffer = (unsigned char *)calloc(1, stat_buf.st_size))) {
		halt("file is too large: \"%s\"\n", g_filename_in);
	}
	if (fread(g_file_buffer, stat_buf.st_size, 1, g_filein) == 0) {
		halt("unable to read file: \"%s\"\n", g_filename_in);
	}
	
	my_pc = start_address;	
	
	// notice some stuff if verbose
	if (start_address != START_ADDRESS) {
		log_notice("using address: \"0x%x\"\n", start_address);
	}
	if (standard_disp) {
		log_notice("using standard displacement\n");
	}

	// do the magic!
	for (i = 0; i < stat_buf.st_size; i += N_O_BITS_BLOCK) {
#ifdef DO_SYMBOL
		if ((my_sym = (char *)symtab_lookup(my_pc)) != NULL) {
			fprintf(g_out, "%s:\n", my_sym);
		}
#endif
		fprintf(g_out, "H'%08x: ", my_pc);

		my_opcode = char2short(&g_file_buffer[i]);
		fprintf(g_out, "H'%04x  ", my_opcode);

		for (j = 0; j < N_O_BITS_BLOCK; j++) {
			fprintf(g_out, "%c", is_alpha(g_file_buffer[i+j]));
		}

		fprintf(g_out, "  %s\n", decode(my_opcode, my_pc, g_file_buffer, stat_buf.st_size, start_address));
		my_pc += N_O_BITS_BLOCK;
	}
	
	return EXIT_SUCCESS;

}
