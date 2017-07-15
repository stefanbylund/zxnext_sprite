/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_pattern() in zxnext_sprite.h.
 ******************************************************************************/

#include <z80.h>
#include <stdint.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_pattern(void *sprite_pattern)
{
    uint16_t i;

    for (i = 0; i < 256; i++)
    {
        IO_SPRITE_PATTERN_PORT = ((uint8_t *) sprite_pattern)[i];
    }

    // TODO: Replace above with below when ZEsarUX treats this port as an 8-bit port.

    // Length 0 means 256 in otir instruction.
    //z80_otir(sprite_pattern, SPRITE_PATTERN_PORT, 0);
}
