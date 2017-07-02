/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of get_sprite_system_state() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

uint8_t get_sprite_system_state(void)
{
    return IO_SPRITE_SLOT_PORT;
}
