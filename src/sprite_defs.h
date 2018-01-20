/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Common definitions used by the implementation of zxnext_sprite.h.
 ******************************************************************************/

#ifndef _SPRITE_DEFS_H
#define _SPRITE_DEFS_H

#include "zxnext_registers.h"

#define SPRITE_SLOT_PORT       0x303B
#define SPRITE_PATTERN_PORT    0x5B
#define SPRITE_ATTRIBUTES_PORT 0x57

#define SPRITES_VISIBLE_MASK   0x01
#define SPRITES_ON_BORDER_MASK 0x02
#define LAYER_PRIORITIES_MASK  0x07
#define LORES_MODE_MASK        0x80
#define LAYER_PRIORITIES_SHIFT 2

#define SPRITE_SLOT_MASK     0x3F
#define X_LSB_MASK           0x00FF
#define X_MSB_MASK           0x0100
#define X_MSB_SHIFT          8
#define PALETTE_OFFSET_SHIFT 4
#define SPRITE_VISIBLE_MASK  0x80

__sfr __banked __at REGISTER_NUMBER_PORT IO_REGISTER_NUMBER_PORT;
__sfr __banked __at REGISTER_VALUE_PORT IO_REGISTER_VALUE_PORT;
__sfr __banked __at SPRITE_SLOT_PORT IO_SPRITE_SLOT_PORT;
__sfr __at SPRITE_PATTERN_PORT IO_SPRITE_PATTERN_PORT;
__sfr __at SPRITE_ATTRIBUTES_PORT IO_SPRITE_ATTRIBUTES_PORT;

#endif
