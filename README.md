# C Hardware Sprite API for Sinclair ZX Spectrum Next

The **zxnext_sprite** project provides a C API for using the hardware sprites of
the Sinclair ZX Spectrum Next as specified at http://www.specnext.com/sprites/.
This API is a thin C wrapper on top of the I/O port interface of the hardware
sprite system.

The [zxnext_sprite_demo](https://github.com/stefanbylund/zxnext_sprite_demo)
project contains a simple example program demonstrating how to use this API.

## Download

The latest version of this API can be downloaded [here](build/zxnext_sprite.zip).
This download contains the following header files and libraries:

* zxnext_sprite/include/zxnext_sprite.h
* zxnext_sprite/include/zxnext_registers.h
* zxnext_sprite/lib/sccz80/zxnext_sprite.lib
* zxnext_sprite/lib/sdcc_ix/zxnext_sprite.lib
* zxnext_sprite/lib/sdcc_iy/zxnext_sprite.lib

If you want to build the zxnext_sprite libraries yourself, see the "How to build"
section below.

## API Documentation

The zxnext_sprite API is documented in the following header files:

* [zxnext_sprite.h](include/zxnext_sprite.h)
* [zxnext_registers.h](include/zxnext_registers.h)

## How to Use

1. Download [zxnext_sprite.zip](build/zxnext_sprite.zip) and unpack it in a
suitable place. It contains the files listed in the "Download" section above.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and
the [ZEsarUX](https://sourceforge.net/projects/zesarux/) or
[CSpect](https://dailly.blogspot.se/2017/07/new-cspect-zx-spectrum-next-emulator.html)
emulator.

4. Read about how hardware sprites work in the "Hardware Sprites" section below
or in the official specification at http://www.specnext.com/sprites/.

5. Familiarize yourself with the zxnext_sprite.h API.

6. Include zxnext_sprite.h in your program and start creating sprites.

7. Compile your program with z88dk and link it with the appropriate version of
zxnext_sprite.lib.

8. Run your program in the ZEsarUX or CSpect emulator.

**Note:** Since the Sinclair ZX Spectrum Next is still under development and all
tools need to catch up with the latest specs, it is important to use the latest
version of z88dk and ZEsarUX or CSpect.

**Tip:** See the [zxnext_sprite_demo](https://github.com/stefanbylund/zxnext_sprite_demo)
project for a simple example of how to use zxnext_sprite.h and link with zxnext_sprite.lib.

**Tip:** If you copy the zxnext_sprite header files and libraries into the
following directories in z88dk, the z88dk compiler will automatically find them
without the need for setting up any include and library paths:

* z88dk/include/_DEVELOPMENT/sccz80/
* z88dk/include/_DEVELOPMENT/sdcc/
* z88dk/libsrc/_DEVELOPMENT/lib/sccz80/
* z88dk/libsrc/_DEVELOPMENT/lib/sdcc_ix/
* z88dk/libsrc/_DEVELOPMENT/lib/sdcc_iy/

**Tip:** To start the ZEsarUX emulator directly in Sinclair ZX Spectrum Next
mode, start it with the following options:

> zesarux --machine tbblue --enable-mmc --enable-divmmc-ports --mmc-file extras/media/disk_images/tbblue.mmc --quickexit

**Tip:** To start the CSpect emulator directly in Sinclair ZX Spectrum Next
mode, start it with the following options:

> CSpect -zxnext -s7 -mmc=<virtual_mmc_root_folder> <my_program>.sna

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

The Sinclair ZX Spectrum Next provides 64 hardware sprites numbered from 0 to
63\. Each sprite is 16 * 16 pixels where each pixel is an 8-bit index between
0 and 255 into a 256-colour sprite palette. Each colour in the palette is an
8-bit RRRGGGBB colour value. The palette colour pink 0xE3 (227) represents
the transparent colour. At reset, the palette is initialized with the colours
0 to 255 using a one-to-one mapping between palette indexes and palette
colours, i.e. palette index 0 contains colour 0, palette index 1 contains
colour 1, ..., palette index 255 contains colour 255.

Tip: If you're drawing your sprites in a general-purpose paint program, it's
good to know that the transparent colour 0xE3 corresponds to the 24-bit RGB
colour 0xE000C0 (224, 0, 192).

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

## License

This software is licensed under the terms of the MIT license.
