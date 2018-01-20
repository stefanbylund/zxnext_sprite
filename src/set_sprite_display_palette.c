/*******************************************************************************
 * Stefan Bylund 2018
 *
 * Implementation of set_sprite_display_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdbool.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_display_palette(bool first_palette)
{
    IO_REGISTER_NUMBER_PORT = PALETTE_CONTROL_REGISTER;
    IO_REGISTER_VALUE_PORT = (IO_REGISTER_VALUE_PORT & 0xF7) | (first_palette ? 0x00 : 0x08);
}
