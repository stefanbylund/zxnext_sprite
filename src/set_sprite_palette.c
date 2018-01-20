/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_palette(const uint16_t *colors, uint16_t length, uint8_t palette_index)
{
    uint8_t *color_bytes = (uint8_t *) colors;
    uint16_t i;

    if ((colors == NULL) || (length == 0))
    {
        return;
    }

    if (palette_index + length > 256)
    {
        length = 256 - palette_index;
    }

    IO_REGISTER_NUMBER_PORT = PALETTE_INDEX_REGISTER;
    IO_REGISTER_VALUE_PORT = palette_index;

    IO_REGISTER_NUMBER_PORT = PALETTE_VALUE_9BIT_REGISTER;
    for (i = 0; i < (length << 1); i++)
    {
        IO_REGISTER_VALUE_PORT = color_bytes[i];
    }
}
