/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <z80.h>
#include <stdint.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_palette(void *sprite_palette)
{
    int i;

    for (i = 0; i < 256; i++)
    {
        IO_SPRITE_PALETTE_PORT = ((uint8_t *) sprite_palette)[i];
    }

    // TODO: Replace above with below when ZEsarUX treats this port as an 8-bit port.

    // Length 0 means 256 in otir instruction.
    //z80_otir(sprite_palette, SPRITE_PALETTE_PORT, 0);
}
