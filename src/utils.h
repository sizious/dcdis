/** 
 * Global utilities
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

#ifndef __UTILS_H__
#define __UTILS_H__

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <libgen.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_YR 9999
#define MIN_YR 1900

void ltrim(char *str);
void rtrim(char *str);
void trim(char *str);

void program_name_initialize(char *argv0);
char * program_name_get();
void program_name_finalize();

void verbose_enable();

void log_notice(const char *format, ...);
void log_warn(const char *format, ...);
void log_error(const char *format, ...);

void halt(const char *format, ...);

int long_parse(char *str, long *result);
int substr_long_parse(char *str, int start, int length, long *result);

int is_valid_date(char *str);
int is_valid_hex(char *str);
int is_strict_bool(char c);

int is_file_exist(char *filename);
int is_file_elf(char *filename);

char * retrieve_parameterized_options(char *opts);
int is_in_char_array(char needle, char *haystack);

void bwrite(size_t *pos, void *dest, const void *source, size_t num);

#endif /* __UTILS_H__ */
