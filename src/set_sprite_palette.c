/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <z80.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_palette(const void *sprite_palette)
{
    // Length 0 means 256 in otir instruction.
    z80_otir((void *) sprite_palette, SPRITE_PALETTE_PORT, 0);
}
