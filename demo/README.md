# Demonstration of zxnext_sprite

This folder contains a simple example program demonstrating how to use the
[zxnext_sprite](https://github.com/stefanbylund/zxnext_sprite) C hardware sprite
API for the ZX Spectrum Next.

**Note:** This demo still works but is a bit out-of-date. It will be updated
someday when I have the time ;)

## How to Build

If you want to build this demo program yourself, follow the steps below:

1. On Windows, you need [MinGW](http://www.mingw.org/),
[UnxUtils](https://sourceforge.net/projects/unxutils/) or
[Cygwin](https://www.cygwin.com/) for the basic Unix commands. Add the chosen
set of Unix commands to your path.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and the
[ZEsarUX](https://github.com/chernandezba/zesarux) or
[CSpect](https://dailly.blogspot.se/) emulator.

3. Download the zxnext_sprite repository either as a ZIP archive using the
"Clone or download" button at the top of this page or with Git using the
following command:

> git clone https://github.com/stefanbylund/zxnext_sprite.git

4. Go to the zxnext_sprite directory and enter the following command to
build the C hardware sprite API for Spectrum Next:

> make all

5. Go to the zxnext_sprite/demo directory and enter the following command to
build the demo program:

> make all

6. Run the zxnext_sprite/demo/bin/\<compiler-flavour\>/zxnext_sprite_demo.nex
file in the ZEsarUX or CSpect emulator.

**Tip:** If you don't care for makefiles or don't want to install
MinGW/UnxUtils/Cygwin on Windows, you can build zxnext_sprite demo manually
by using the z88dk command-line invocation located in the header of the
zxnext_sprite_demo.c source file.

**Tip:** To start the ZEsarUX emulator directly in Spectrum Next mode, start it
with the following options:

> zesarux --noconfigfile --machine tbblue --enabletimexvideo --tbblue-fast-boot-mode
  --quickexit --enable-esxdos-handler --esxdos-root-dir <zxnext_sprite_demo_folder>
  zxnext_sprite_demo.nex

**Tip:** To start the CSpect emulator directly in Spectrum Next mode, start it
with the following options:

> CSpect -w2 -tv -zxnext -mmc=<zxnext_sprite_demo_folder>/ zxnext_sprite_demo.nex

## License

This software is licensed under the terms of the MIT license.
