/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_layers_system() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <arch/zxn.h>
#include "zxnext_sprite.h"

#define LAYER_PRIORITIES_MASK  0x07
#define LAYER_PRIORITIES_SHIFT 2

void set_sprite_layers_system(bool sprites_visible,
                              bool sprites_on_border,
                              uint8_t layer_priorities,
                              bool lores_mode)
{
    uint8_t value = (layer_priorities & LAYER_PRIORITIES_MASK) << LAYER_PRIORITIES_SHIFT;

    if (sprites_visible)
    {
        value = value | RSLS_SPRITES_VISIBLE;
    }

    if (sprites_on_border)
    {
        value = value | RSLS_SPRITES_OVER_BORDER;
    }

    if (lores_mode)
    {
        value = value | RSLS_ENABLE_LORES;
    }

    IO_NEXTREG_REG = REG_SPRITE_LAYER_SYSTEM;
    IO_NEXTREG_DAT = value;
}
