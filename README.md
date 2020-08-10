# Dreamcast disassembler (dcdis)

**dcdis** is a very simple Sega Dreamcast(tm) disassembler initially made by [Lars Olsson](https://lars-olsson.sizious.com/) (Maiwe).

This tool produces text files which contains all the disassembled code for the main CPU, the Hitachi SH7750 (SH-4).

## Building



## Usage & features

The usage of **dcdis** is very simple, it can be used as the follow:

	dcdis [options] <dcprog.bin>

The following options are supported:

	-b<address>    binary file, text start
	-o<filename>   file to write output to (default: stdout)
	-s<filename>   Katana MAP file
	-d             standard displacement

	<filename>     file to disassemble

0x8c010000

## Acknowledgments

* [Lars Olsson](jlo@ludd.luth.se) (Maiwe): Initial maker of the dcdis tool;
* [Moopthehedgehog](https://dcemulation.org/phpBB/viewtopic.php?t=105372): Port to modern ANSI C.
* [SiZiOUS](https://sizious.com): Additional improvements and fixes.
 
## License

**dcdis** is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file for more information.
