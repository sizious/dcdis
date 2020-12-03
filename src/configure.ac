# configure.in for dcdis
# Process this file with autoconf to generate a configuration script.
#
# Copyright (C) 1999-2004 Lars Olsson (Maiwe)
# Copyright (C) 2019 Moopthehedgehog
# Copyright (C) 2020 SiZiOUS
#
# This file is part of dcdis.

# dcdis is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Minimum Autoconf version required.
AC_PREREQ(2.59)

# Initialize
AC_INIT([dcdis], [1.0.0])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_SRCDIR([dcdis.c])

# Check for a working compiler
AC_PROG_CC

# Check for a BSD compatible install
AC_PROG_INSTALL

# Every system should have this...
AC_CHECK_HEADERS([stdio.h],,exit -1)

# Check if all functions are available
AC_CHECK_FUNCS([fprintf fopen fread stat],,exit -1)
AC_CHECK_FUNCS([sscanf strstr memcpy],,)

AC_OUTPUT([Makefile])
