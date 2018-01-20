/*******************************************************************************
 * Stefan Bylund 2018
 *
 * Implementation of reset_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void reset_sprite_palette(void)
{
    uint16_t i;

    IO_REGISTER_NUMBER_PORT = PALETTE_INDEX_REGISTER;
    IO_REGISTER_VALUE_PORT = 0;

    IO_REGISTER_NUMBER_PORT = PALETTE_VALUE_8BIT_REGISTER;
    for (i = 0; i < 256; i++)
    {
        IO_REGISTER_VALUE_PORT = (uint8_t) i;
    }
}
