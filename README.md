# C Hardware Sprite API for Sinclair ZX Spectrum Next

The **zxnext_sprite** project provides a C API for using the hardware sprites of
the Sinclair ZX Spectrum Next as specified at https://www.specnext.com/sprites/.
This API is a thin C wrapper on top of the I/O port interface of the hardware
sprite system.

The [zxnext_sprite_demo](https://github.com/stefanbylund/zxnext_sprite_demo)
project contains a simple example program demonstrating how to use this API.

**Note:** This project still works but is a bit out-of-date. It will be updated
someday when I have the time ;)

## Download

The latest version of this API can be downloaded here:

* [zxnext_sprite.zip](build/zxnext_sprite.zip)
* [zxnext_sprite_z88dk.zip](build/zxnext_sprite_z88dk.zip)

The zxnext_sprite.zip archive contains the following header file and libraries:

* zxnext_sprite/include/zxnext_sprite.h
* zxnext_sprite/lib/sccz80/zxnext_sprite.lib
* zxnext_sprite/lib/sdcc_ix/zxnext_sprite.lib
* zxnext_sprite/lib/sdcc_iy/zxnext_sprite.lib

The zxnext_sprite_z88dk.zip archive contains a packaging of zxnext_sprite that
can be installed directly into your z88dk installation for convenience, see the
tip below.

If you want to build the zxnext_sprite libraries yourself, see the "How to Build"
section below.

## API Documentation

The zxnext_sprite API is documented in the following header file:

* [zxnext_sprite.h](include/zxnext_sprite.h)

## How to Use

1. Download [zxnext_sprite.zip](build/zxnext_sprite.zip) and unpack it in a
suitable place. It contains the files listed in the "Download" section above.
For convenience, you can instead download
[zxnext_sprite_z88dk.zip](build/zxnext_sprite_z88dk.zip) and install it into
your z88dk installation, see the tip below.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and
the [ZEsarUX](https://github.com/chernandezba/zesarux) or
[CSpect](https://dailly.blogspot.se/) emulator.

4. Read about how hardware sprites work in the "Hardware Sprites" section below
or in the official specification at http://www.specnext.com/sprites/.

5. Familiarize yourself with the zxnext_sprite.h API.

6. Include zxnext_sprite.h in your program and start creating sprites.

7. Compile your program with z88dk and link it with the appropriate version of
zxnext_sprite.lib.

8. Run your program in the ZEsarUX or CSpect emulator.

**Tip:** See the [zxnext_sprite_demo](https://github.com/stefanbylund/zxnext_sprite_demo)
project for a simple example of how to use zxnext_sprite.h and link with zxnext_sprite.lib.

**Tip:** You can install zxnext_sprite into your z88dk installation by using
its third-party library installer z88dk-lib. Unpack the zxnext_sprite_z88dk.zip
archive in a temporary directory, go to this directory (where the unpacked
zxnext_sprite subdirectory is located) and enter the following command:

> z88dk-lib +zxn -f zxnext_sprite

The -f option will make z88dk-lib overwrite any existing files without
confirmation (e.g. if you update zxnext_sprite it will replace the older version).
Run z88dk-lib without any arguments to see a list of all its options.

The z88dk compiler will now automatically find the zxnext_sprite header file and
library without the need for setting up any include and library paths. The
zxnext_sprite.h header file is now included with **#include <lib/zxn/zxnext_sprite.h>**
and the zxnext_sprite.lib library is linked against using **-llib/zxn/zxnext_sprite**.

**Tip:** To start the ZEsarUX emulator directly in Sinclair ZX Spectrum Next
mode, start it with the following options:

> zesarux --noconfigfile --machine tbblue --enabletimexvideo --tbblue-fast-boot-mode
  --quickexit --enable-esxdos-handler --esxdos-root-dir <virtual_mmc_root_folder>
  <my_program>.nex

**Tip:** To start the CSpect emulator directly in Sinclair ZX Spectrum Next
mode, start it with the following options:

> CSpect -w2 -tv -zxnext -mmc=<virtual_mmc_root_folder>/ <my_program>.nex

## How to Build

If you want to build the zxnext_sprite libraries yourself, follow the steps below:

1. On Windows, you need [MinGW](http://www.mingw.org/),
[UnxUtils](https://sourceforge.net/projects/unxutils/) or
[Cygwin](https://www.cygwin.com/) for the basic Unix commands. Add the chosen
set of Unix commands to your path.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and add
it to your path.

3. Download the zxnext_sprite repository either as a ZIP archive using the
"Clone or download" button at the top of this page or with Git using the
following command:

> git clone https://github.com/stefanbylund/zxnext_sprite.git

4. Go to the zxnext_sprite repository and enter the following command:

> make all

## Hardware Sprites

The Sinclair ZX Spectrum Next provides 64 hardware sprites numbered from 0 to 63.
Each sprite is 16 * 16 pixels where each pixel is an 8-bit index between
0 and 255 into a 256-colour sprite palette. The sprite pixels are laid out
linearly from left to right and top to bottom.

The sprite palette consists of 256 9-bit RGB333 colour values, i.e. the total
number of colours is 512. There are actually two sprite palettes, which one
is currently used for diplaying the sprites can be selected at runtime. The
colour encoding of the sprite palette is the same as for the palette of the
ULA and layer 2 screens.

At reset, the sprite palette is initialized with the RGB332 colours 0 to 255
using a one-to-one mapping between palette indexes and palette colours, i.e.
palette index 0 contains colour 0, palette index 1 contains colour 1, ...,
palette index 255 contains colour 255. The effective palette colours will be
9-bit RGB333 colours where the lower blue bit is an OR between bit 1 and bit
0 in the 8-bit RGB332 colours.

One colour is defined as the global transparency colour. This colour is an
8-bit RGB332 colour value so the transparency is compared only with the 8
most significant bits of the 9-bit RGB333 colours in the sprite palette. This
means that two of the 512 possible RGB333 colours will be transparent. By
default, the global transparency colour is set to the pink colour 0xE3 (227).

Tip: If you're drawing your sprites in a general-purpose paint program, it's
good to know that the default global transparency colour 0xE3 corresponds to
the 24-bit RGB colour 0xE000C0 (224, 0, 192).

Sprites can optionally be rendered on the border of the screen. The coordinate
system of the sprites therefore includes the border, which is 32 pixels, and
the total sprite resolution is thus 320 * 256 pixels. The standard screen
resolution is 256 * 192 pixels. This means that if sprites is not rendered on
the border, the sprite coordinates range from (32, 32) to (287, 223).

For convenience, there is an extended version of the set_sprite_attributes()
function, for setting the sprite position, called set_sprite_attributes_ext(),
which accepts screen-based coordinates (256 * 192 pixels) and internally
converts them to border-based coordinates (320 * 256 pixels). This function
is convenient if you prefer to work in screen coordinates and don't want to
render the sprites on the border area.

When using the sprites there is a differentiation between the actual sprites
and the sprite pattern (i.e. the sprite bitmap) used by the sprites. There
are 64 sprites and 64 sprite patterns. The sprite patterns are defined
independently of the sprites and are referenced by the sprites. This means
that multiple sprites can share the same sprite pattern.

The sprite pattern is set for the currently selected sprite pattern slot
(0 - 63). The attributes of a sprite is set for the currently selected sprite
slot (0 - 63). The sprite attributes determine which sprite pattern the sprite
should use, the x and y position of the sprite, an optional sprite palette
offset, a bit-mask of flags for sprite mirroring and rotation, and whether or
not the sprite should be visible.

If the optional sprite palette offset (0 - 15) is used when setting the
attributes of a sprite, it is added to the 4 most significant bits of each
8-bit palette index in the sprite pattern of the sprite. In this way, the
256-colour sprite palette is effectively divided into 16 sub-palettes
numbered from 0 to 15 where each sub-palette contains 16 colours indexed from
0 to 15. The palette offset then controls which of the 16 sub-palettes should
be used. For example, if a pixel in a sprite pattern contains the palette
index 0x14, which denotes the colour at index 4 in sub-palette 1, and the
palette offset is 2, the actual palette index used for that pixel will be
0x34, which denotes the colour at index 4 in sub-palette 3 (sub-palette 1 +
palette offset 2). When the palette offset is added to a sub-palette number,
the addition is actually done in modulo 16. For example, adding palette
offset 5 to sub-palette number 13 gives sub-palette number 2. If used, the
palette offset is an efficient way of displaying the same sprite pattern in
different colours.

The priority between the sprites is determined by the sprite slot number.
Sprite 0 has the lowest priority and sprite 63 has the highest priority.
A sprite with a higher priority is drawn over a sprite with lower priority.
The layer priority between the sprites and the layer 2 and ULA screens is
configurable, the default priority is sprites over layer 2 screen over ULA
screen.

There can be a maximum of 12 sprites per scanline. Whether or not this limit
has been reached for any scanline can be queried. If there are more than 12
sprites on a scanline, only the 12 sprites with the highest priority are
displayed.

The sprite system provides collision detection of the sprites. A collision of
two or more sprites happen if a non-transparent pixel of the sprites are drawn
in the same position on the screen. The sprite system only informs whether a
sprite collision has occurred or not, which sprites has actually collided must
be determined in software.

## Known Problems

None.

## License

This software is licensed under the terms of the MIT license.
