/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of get_sprite_system_state() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <arch/zxn.h>
#include "zxnext_sprite.h"

uint8_t get_sprite_system_state(void)
{
    return IO_SPRITE_SLOT;
}
