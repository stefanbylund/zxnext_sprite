/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_attributes_ext() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

#define X_EXT(x) (((uint16_t) (x)) + 32)

#define X_LSB(x_ext) (uint8_t) ((x_ext) & X_LSB_MASK)

#define X_MSB(x_ext) (uint8_t) (((x_ext) & X_MSB_MASK) >> X_MSB_SHIFT)

#define Y_EXT(y) ((y) + 32)

void set_sprite_attributes_ext(uint8_t sprite_pattern_slot,
                               uint8_t x,
                               uint8_t y,
                               uint8_t palette_offset,
                               uint8_t sprite_flags,
                               bool visible)
{
    uint8_t pattern_slot = sprite_pattern_slot & SPRITE_SLOT_MASK;

    if (visible)
    {
        pattern_slot = pattern_slot | SPRITE_VISIBLE_MASK;
    }

    IO_SPRITE_ATTRIBUTES_PORT = X_LSB(X_EXT(x));
    IO_SPRITE_ATTRIBUTES_PORT = Y_EXT(y);
    IO_SPRITE_ATTRIBUTES_PORT = (palette_offset << PALETTE_OFFSET_SHIFT) | X_MSB(X_EXT(x)) | sprite_flags;
    IO_SPRITE_ATTRIBUTES_PORT = pattern_slot;
}
