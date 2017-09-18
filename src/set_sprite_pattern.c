/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_pattern() in zxnext_sprite.h.
 ******************************************************************************/

#include <intrinsic.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_pattern(const void *sprite_pattern)
{
    intrinsic_outi((void *) sprite_pattern, SPRITE_PATTERN_PORT, 256);
}
