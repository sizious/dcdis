/** 
 * Global utilities definitions
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

#include "utils.h"

int g_verbose = 0;
char *g_program_name;

void
program_name_initialize(char *argv0)
{
  char *result = basename(argv0);
  char *buf = strrchr(result, '.');
  if (buf != NULL) {
    int offset = buf - result;
    result[offset] = '\0';
  }
  g_program_name = strdup(result);
}

char *
program_name_get()
{
  return g_program_name;
}

void
program_name_finalize()
{
  free(g_program_name);	
}

void
log_notice(const char *format, ...)
{
  if (g_verbose) {
    va_list args;
  
    fprintf(stdout, "%s: ", g_program_name);
  
    va_start(args, format);  
    vfprintf(stdout, format, args);
    va_end(args);
  }
}

void
log_warn(const char *format, ...)
{
  va_list args;
  
  fprintf(stdout, "%s: warning: ", g_program_name);
  
  va_start(args, format);  
  vfprintf(stdout, format, args);
  va_end(args);
}

void
log_error(const char *format, ...)
{
  va_list args;
  
  fprintf(stderr, "%s: error: ", g_program_name);
  
  va_start(args, format);  
  vfprintf(stderr, format, args);
  va_end(args);
}

void
halt(const char *format, ...)
{
  va_list args;
  
  fprintf(stderr, "%s: fatal: ", g_program_name);
  
  va_start(args, format);  
  vfprintf(stderr, format, args);
  va_end(args);
  
  exit(EXIT_FAILURE);
}

void
verbose_enable()
{
  g_verbose = 1;	
}

int
is_file_exist(char *filename)
{
  struct stat stats;
  return (stat(filename, &stats) == 0);
}

int
is_in_char_array(char needle, char *haystack)
{
  for(int i = 0; i < strlen(haystack); i++)
  {
    if(haystack[i] == needle)
      return 1;
  }
  return 0;  
}

char *
retrieve_parameterized_options(char *opts)
{
  char c = '\0';
  int j = 0;

  char *buf = (char *) malloc(strlen(opts) * sizeof(char));
  memset(buf, '\0', strlen(opts));
  
  for(int i = 0; i < strlen(opts); i++) {
    if (opts[i]	== ':' && c != '\0') {
      buf[j++] = c;
      c = '\0';	  
	}
	c = opts[i];
  }
  
  return buf; // must be destroyed later
}

int
is_file_elf(char *filename)
{
  char data[4];
  
  memset(data, 0x0, sizeof(data));

  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    log_error("elf: can't open file: \"%s\"\n", filename);
    return 0;
  }
  
  int result = 1;
  if (!fread(data, sizeof(data), 1, f)) {
    log_error("elf: unable to read file\n");
    result = 0;
  }
  
  fclose(f);
  
  if (result) {
	if (!memcmp(data + 1, "ELF", 3)) {
		return 1;
	}
  }
  
  return 0;
}
