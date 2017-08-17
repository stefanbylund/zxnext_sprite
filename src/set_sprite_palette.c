/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <intrinsic.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_palette(const void *sprite_palette)
{
    intrinsic_outi((void *) sprite_palette, SPRITE_PALETTE_PORT, 256);
}
