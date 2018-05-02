/*******************************************************************************
 * Stefan Bylund 2018
 *
 * Implementation of set_sprite_rw_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdbool.h>
#include <arch/zxn.h>
#include "zxnext_sprite.h"

void set_sprite_rw_palette(bool first_palette)
{
    IO_NEXTREG_REG = REG_PALETTE_CONTROL;
    IO_NEXTREG_DAT = (IO_NEXTREG_DAT & 0x8F) | (first_palette ? 0x20 : 0x60);
}
