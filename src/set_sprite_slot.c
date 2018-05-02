/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of set_sprite_slot() in zxnext_sprite.h.
 ******************************************************************************/

#include <stdint.h>
#include <arch/zxn.h>
#include "zxnext_sprite.h"
#include "sprite_defs.h"

void set_sprite_slot(uint8_t sprite_slot)
{
    IO_SPRITE_SLOT = sprite_slot & SPRITE_SLOT_MASK;
}
