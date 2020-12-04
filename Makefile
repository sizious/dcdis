# dcdis Makefile for KallistiOS
#
# Copyright (C) 1999-2004 Lars Olsson (Maiwe)
# Copyright (C) 2019 Moopthehedgehog
# Copyright (C) 2020 SiZiOUS
#
# This file is part of dcdis.

# dcdis is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

MAKE ?= make

all:
	@if test ! -d "$(KOS_BASE)"; then \
		echo "Error: KallistiOS was not detected, cannot continue in this mode"; \
		exit 1; \
	fi; \
	cd ./src; \
	if test ! -f "Makefile"; then \
		echo "Configuring dcdis in KallistiOS mode..."; \
		./configure --prefix=$(CURDIR); \
	fi; \
	$(MAKE) install-kos;

clean:
	@cd ./src; \
	$(MAKE) clean

distclean:
	@cd ./src; \
	$(MAKE) distclean
