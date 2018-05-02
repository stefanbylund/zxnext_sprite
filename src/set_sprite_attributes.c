/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_attributes() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <arch/zxn.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

#define X_LSB(x) (uint8_t) ((x) & X_LSB_MASK)

#define X_MSB(x) (uint8_t) (((x) & X_MSB_MASK) >> X_MSB_SHIFT)

void set_sprite_attributes(uint8_t sprite_pattern_slot,
                           uint16_t x,
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

    IO_SPRITE_ATTRIBUTE = X_LSB(x);
    IO_SPRITE_ATTRIBUTE = y;
    IO_SPRITE_ATTRIBUTE = (palette_offset << PALETTE_OFFSET_SHIFT) | X_MSB(x) | sprite_flags;
    IO_SPRITE_ATTRIBUTE = pattern_slot;
}
