# configure.in for dcdis
# Process this file with autoconf to generate a configuration script.
#
# Copyright (C) 1999 Lars Olsson
#
# This file is part of dcdis.

# dcdis is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

MAKE ?= make
TOOLCHAINS_BASE = ${KOS_BASE}/..

all:
	@cd ./src \
	&& ./configure --prefix=$(TOOLCHAINS_BASE) \
	&& $(MAKE) \
	&& $(MAKE) install

clean:
	@cd ./src \
	&& $(MAKE) clean

distclean:
	@cd ./src \
	&& $(MAKE) distclean
