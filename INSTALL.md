# Sega Dreamcast Disassembler (dcdis): Installing

You have 2 modes to build and install **dcdis**:

1. KallistiOS mode
2. Standalone mode

## KallistiOS Mode

Starting from `v1.0.0`, **dcdis** is ready to be integrated in a KallistiOS
installation, in the `utils` directory. The `Makefile` located in the root
directory is designed for that use case.

Input the following to install **dcdis** in your KallistiOS utilities
directory:

	git clone https://github.com/sizious/dcdis.git ${KOS_BASE}/utils/dcdis
	cd ${KOS_BASE}/utils/dcdis
	make
	
The `dcdis` binary will be installed in the `/opt/toolchains/bin/` directory.

## Standalone Mode

If you want to use **dcdis** in a standalone mode, i.e. without KallistiOS, then
you may do it by following instructions of this section. You just need a working
GCC toolchain in order to do that.

In that case, for most machines and configurations, the following is all you
need:

	cd src
	./configure
	make
	make install


In standalone, i.e. in manual installation mode, **dcdis** will be installed in
`/usr/local/bin` by default, but this can be altered by specifying another
location to `configure` using this formula:


	./configure --prefix=/installation/directory

You may read the [README.md](README.md) for more information on this project.