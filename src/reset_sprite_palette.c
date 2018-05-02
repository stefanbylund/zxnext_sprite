/*******************************************************************************
 * Stefan Bylund 2018
 *
 * Implementation of reset_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <arch/zxn.h>
#include "zxnext_sprite.h"

void reset_sprite_palette(void)
{
    uint16_t i;

    IO_NEXTREG_REG = REG_PALETTE_INDEX;
    IO_NEXTREG_DAT = 0;

    IO_NEXTREG_REG = REG_PALETTE_VALUE_8;
    for (i = 0; i < 256; i++)
    {
        IO_NEXTREG_DAT = (uint8_t) i;
    }
}
