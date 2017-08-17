/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_pattern() in zxnext_sprite.h.
 ******************************************************************************/

#include <intrinsic.h>
#include <stdint.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_pattern(const void *sprite_pattern)
{
// intrinsic_outi() works in ZEsarUX but not in CSpect.
#ifdef USE_OUTI
    intrinsic_outi((void *) sprite_pattern, SPRITE_PATTERN_PORT, 256);
#else
    uint16_t i;

    for (i = 0; i < 256; i++)
    {
        IO_SPRITE_PATTERN_PORT = ((uint8_t *) sprite_pattern)[i];
    }
#endif
}
