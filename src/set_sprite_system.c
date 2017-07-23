/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_system() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_system(bool sprites_visible, bool sprites_on_border, uint8_t layer_priorities)
{
    uint8_t value = (layer_priorities & LAYER_PRIORITIES_MASK) << LAYER_PRIORITIES_SHIFT;

    if (sprites_visible)
    {
        value = value | SPRITES_VISIBLE_MASK;
    }

    if (sprites_on_border)
    {
        value = value | SPRITES_ON_BORDER_MASK;
    }

    IO_REGISTER_NUMBER_PORT = SPRITE_SYSTEM_REGISTER;
    IO_REGISTER_VALUE_PORT = value;
}
