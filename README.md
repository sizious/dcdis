# Dreamcast disassembler (dcdis)

**dcdis** is a very simple Sega Dreamcast(tm) disassembler initially made
by [Lars Olsson](https://lars-olsson.sizious.com/) (Maiwe).

This tool produces text files which contains all the disassembled code of any
Sega Dreamcast executable. The Dreamcast's CPU, a Hitachi SH7091, is virtually
identical to the Renesas SH7750 series of SH4 CPUs. **dcdis** will produces
a disassembled text file containing SH7091/SH7750 instructions.

## Building & installing

You have 2 modes to use **dcdis**:
1. KallistiOS integration mode
2. Standalone mode

### KallistiOS

Starting from `Ver. 0.6a`, **dcdis** is ready to be integrated in a KallistiOS
installation, in the `utils` directory.

In that case, you may input the following:

	git clone https://github.com/sizious/dcdis.git ${KOS_BASE}/utils/dcdis
	cd ${KOS_BASE}/utils/dcdis
	make
	
The `dcdis` binary will be installed in the `/opt/toolchains/bin/` directory.

### Standalone

If you want to use **dcdis** in a standalone mode, i.e. without KallistiOS, then
you may do it by following instructions of this section.

In that case, for most machines and configurations, the following is all you
need:

	cd src
	./configure
	make
	make install


In standalone, manual installation mode, **dcdis** will be installed in
`/usr/local/bin` by default, but this can be altered by specifying another
location to `configure` using this formula:


	./configure --prefix=/installation/directory


## Usage & features

The usage of **dcdis** is very simple, it can be used as the follow:

	dcdis [options] <dcprog.bin>

The following options are supported:

	-b<address>    binary file, text start (default: 0x8c010000)
	-o<filename>   file to write output to (default: stdout)
	-s<filename>   use Sega Katana MAP file
	-d             standard displacement

	<filename>     file to disassemble

## Acknowledgments

* [Lars Olsson](jlo@ludd.luth.se) (Maiwe): Initial maker of the dcdis tool;
* [Moopthehedgehog](https://dcemulation.org/phpBB/viewtopic.php?t=105372): Port
  to modern ANSI C.
* [SiZiOUS](https://sizious.com): Additional improvements and fixes.
 
## License

**dcdis** is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the [LICENSE](LICENSE) file for more information.
