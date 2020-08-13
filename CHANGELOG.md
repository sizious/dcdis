# Sega Dreamcast Disassembler (dcdis): Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [1.0.0] - 2020-08-XX
### Changed
- The project was completely refactored to be integrated in the
  [KallistiOS](http://gamedev.allusion.net/softprj/kos/) official repository.
  It's now considered stable so the alpha (`a`) indicator was removed from the
  version number.
- Removing some warnings, the code compiles smoothly on GCC.
- The `HISTORY` (this file), `README` and `INSTALL` files were completely
  redesigned.

### Fixed
- Under Windows, the binary file to disassemble was not loaded properly.


## [0.5.0a] - 2019-12-10
### Changed
- The project is not maintained by *Lars Olsson* (*Maiwe*) anymore.
- The tool is now compatible with modern ANSI C compilers [*Moopthehedgehog*].
  See [DCEmulation](https://dcemulation.org/phpBB/viewtopic.php?f=29&t=105372)
  for more information.


## [0.4.0a] - 2004-03-31
### Changed
- Major clean-up in code-style.

### Fixed
- Minor, undocumented fixes.


## [0.3.3a] - 2000-08-13
### Added
- Switch for standard displacement (e.g. instructions that were previously
interpretted like `mov.l R0, (1, GBR)` is, with this switch, interpretted as
`mov.l R0, (H'004, GBR)`).

### Fixed
- Typo in definition for `FSCA` instruction.
- Representation of `DRx` registers are now correct (i.e. `DR0`, `DR2`, `DR4`...
  instead of `DR0`, `DR1`, `DR2`).


## [0.3.2a] - 2000-08-07
### Fixed
- Fixed a bug in the symbol table that caused some symbols to not be registered
  properly.


## [0.3.1a] - 2000-07-09
### Removed
- Some floating point instructions because they weren't properly decoded since
  this would require keeping track of `FPSCR`.


## [0.3.0a] - 1999-11-24
### Added
- Two missing Sega Dreamcast opcodes.
- Limited cross referencing.

### Changed
- Rewrote symbol table handler to use hash-table.


## [0.2.0a] - 1999-11-04
### Added
- Limited symbol table support.

### Changed
- Some stuff in instruction decoding.


## [0.1.0a] - 1999-10-04
First, very simple version.
Only sent to a couple of people.
