/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_pattern() in zxnext_sprite.h.
 ******************************************************************************/

#include <z80.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_pattern(const void *sprite_pattern)
{
    // Length 0 means 256 in otir instruction.
    z80_otir((void *) sprite_pattern, SPRITE_PATTERN_PORT, 0);
}
