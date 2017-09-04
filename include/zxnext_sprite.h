/*******************************************************************************
 * Stefan Bylund 2017
 *
 * C API for using the hardware sprites of the Sinclair ZX Spectrum Next as
 * specified at http://www.specnext.com/sprites/. This C API is a thin wrapper
 * on top of the I/O port interface of the hardware sprites.
 *
 * The Sinclair ZX Spectrum Next provides 64 hardware sprites numbered from 0 to
 * 63. Each sprite is 16 * 16 pixels where each pixel is an 8-bit index between
 * 0 and 255 into a 256-colour sprite palette. Each colour in the palette is an
 * 8-bit RRRGGGBB colour value. The palette colour pink 0xE3 (227) represents
 * the transparent colour. At reset, the palette is initialized with the colours
 * 0 to 255 using a one-to-one mapping between palette indexes and palette
 * colours, i.e. palette index 0 contains colour 0, palette index 1 contains
 * colour 1, ..., palette index 255 contains colour 255.
 *
 * Tip: If you're drawing your sprites in a general-purpose paint program, it's
 * good to know that the transparent colour 0xE3 corresponds to the 24-bit RGB
 * colour 0xE000C0 (224, 0, 192).
 *
 * Sprites can optionally be rendered on the border of the screen. The coordinate
 * system of the sprites therefore includes the border, which is 32 pixels, and
 * the total sprite resolution is thus 320 * 256 pixels. The standard screen
 * resolution is 256 * 192 pixels. This means that if sprites is not rendered on
 * the border, the sprite coordinates range from (32, 32) to (287, 223).
 *
 * For convenience, there is an extended version of the set_sprite_attributes()
 * function, for setting the sprite position, called set_sprite_attributes_ext(),
 * which accepts screen-based coordinates (256 * 192 pixels) and internally
 * converts them to border-based coordinates (320 * 256 pixels). This function
 * is convenient if you prefer to work in screen coordinates and don't want to
 * render the sprites on the border area.
 *
 * When using the sprites there is a differentiation between the actual sprites
 * and the sprite pattern (i.e. the sprite bitmap) used by the sprites. There
 * are 64 sprites and 64 sprite patterns. The sprite patterns are defined
 * independently of the sprites and are referenced by the sprites. This means
 * that multiple sprites can share the same sprite pattern.
 *
 * The sprite pattern is set for the currently selected sprite pattern slot
 * (0 - 63). The attributes of a sprite is set for the currently selected sprite
 * slot (0 - 63). The sprite attributes determine which sprite pattern the sprite
 * should use, the x and y position of the sprite, an optional sprite palette
 * offset, a bit-mask of flags for sprite mirroring and rotation, and whether or
 * not the sprite should be visible.
 *
 * If the optional sprite palette offset (0 - 15) is used when setting the
 * attributes of a sprite, it is added to the 4 most significant bits of each
 * 8-bit palette index in the sprite pattern of the sprite. In this way, the
 * 256-colour sprite palette is effectively divided into 16 sub-palettes
 * numbered from 0 to 15 where each sub-palette contains 16 colours indexed from
 * 0 to 15. The palette offset then controls which of the 16 sub-palettes should
 * be used. For example, if a pixel in a sprite pattern contains the palette
 * index 0x14, which denotes the colour at index 4 in sub-palette 1, and the
 * palette offset is 2, the actual palette index used for that pixel will be
 * 0x34, which denotes the colour at index 4 in sub-palette 3 (sub-palette 1 +
 * palette offset 2). When the palette offset is added to a sub-palette number,
 * the addition is actually done in modulo 16. For example, adding palette
 * offset 5 to sub-palette number 13 gives sub-palette number 2. If used, the
 * palette offset is an efficient way of displaying the same sprite pattern in
 * different colours.
 *
 * The priority between the sprites is determined by the sprite slot number.
 * Sprite 0 has the lowest priority and sprite 63 has the highest priority.
 * A sprite with a higher priority is drawn over a sprite with lower priority.
 * The layer priority between the sprites and the layer 2 and ULA screens is
 * configurable, the default priority is sprites over layer 2 screen over ULA
 * screen.
 *
 * There can be a maximum of 12 sprites per scanline. Whether or not this limit
 * has been reached for any scanline can be queried. If there are more than 12
 * sprites on a scanline, only the 12 sprites with the highest priority are
 * displayed.
 *
 * The sprite system provides collision detection of the sprites. A collision of
 * two or more sprites happen if a non-transparent pixel of the sprites are drawn
 * in the same position on the screen. The sprite system only informs whether a
 * sprite collision has occurred or not, which sprites has actually collided must
 * be determined in software.
 ******************************************************************************/

#ifndef _ZXNEXT_SPRITE_H
#define _ZXNEXT_SPRITE_H

#include <stdint.h>
#include <stdbool.h>

/* Sprites over layer 2 screen over ULA screen (default). */
#define LAYER_PRIORITIES_S_L_U 0x0

/* Layer 2 screen over sprites over ULA screen. */
#define LAYER_PRIORITIES_L_S_U 0x1

/* Sprites over ULA screen over layer 2 screen. */
#define LAYER_PRIORITIES_S_U_L 0x2

/* Layer 2 screen over ULA screen over sprites. */
#define LAYER_PRIORITIES_L_U_S 0x3

/* ULA screen over sprites over layer 2 screen. */
#define LAYER_PRIORITIES_U_S_L 0x4

/* ULA screen over layer 2 screen over sprites. */
#define LAYER_PRIORITIES_U_L_S 0x5

/* Max sprites per scanline limit reached. */
#define MAX_SPRITES_PER_SCANLINE_MASK 0x02

/* A collision between two or more sprites. */
#define SPRITE_COLLISION_MASK 0x01

/* Mirror the sprite x-wise. */
#define MIRROR_X_MASK 0x08

/* Mirror the sprite y-wise. */
#define MIRROR_Y_MASK 0x04

/* Rotate the sprite 90 degrees. */
#define ROTATE_MASK 0x02

/*
 * Set the sprite and layers system properties. Specify if the sprites should be
 * visible, if they should be rendered on the border of the screen, the layer
 * priority between the sprites and the layer 2 and ULA screens
 * (LAYER_PRIORITIES_S_L_U etc), and if the low-resolution ULA screen mode
 * should be enabled.
 */
void set_sprite_layers_system(bool sprites_visible,
                              bool sprites_on_border,
                              uint8_t layer_priorities,
                              bool lores_mode);

/*
 * Returns the state of the sprite system as a bit-mask informing if the maximum
 * number of sprites per scanline limit has been reached (MAX_SPRITES_PER_SCANLINE_MASK)
 * and if two or more sprites has collided (SPRITE_COLLISION_MASK).
 */
uint8_t get_sprite_system_state(void);

/*
 * Set the sprite colour palette. The palette should contain 256 8-bit RRRGGGBB
 * colours.
 */
void set_sprite_palette(const void *sprite_palette);

/*
 * Set the sprite slot used for the set_sprite_pattern() or set_sprite_attributes()
 * function. The sprite slot is a number between 0 and 63.
 */
void set_sprite_slot(uint8_t sprite_slot);

/*
 * Set the sprite pattern data for the selected sprite pattern slot. The sprite
 * pattern data should be 16 * 16 pixels where each pixel is an 8-bit index
 * between 0 and 255 into the 256-colour sprite palette. The pixels are laid out
 * left to right and top to bottom.
 *
 * After each call to set_sprite_pattern(), the current sprite pattern slot is
 * automatically incremented.
 */
void set_sprite_pattern(const void *sprite_pattern);

/*
 * Set the sprite attributes for the selected sprite slot. The given coordinates
 * are border-based (320 * 256 pixels).
 *
 * The sprite attributes determine which sprite pattern the sprite should use,
 * the x and y position of the sprite, an optional sprite palette offset
 * (0 - 15, set to 0 if not used), a bit-mask of sprite flags (MIRROR_X_MASK,
 * MIRROR_Y_MASK, ROTATE_MASK) or 0 if not set, and whether or not the sprite
 * should be visible.
 *
 * After each call to set_sprite_attributes(), the current sprite slot is
 * automatically incremented.
 */
void set_sprite_attributes(uint8_t sprite_pattern_slot,
                           uint16_t x,
                           uint8_t y,
                           uint8_t palette_offset,
                           uint8_t sprite_flags,
                           bool visible);

/*
 * Set the sprite attributes for the selected sprite slot. The given coordinates
 * are screen-based (256 * 192 pixels) and internally converted to border-based
 * coordinates (320 * 256 pixels). This function is convenient if you prefer to
 * work in screen coordinates and don't want to render the sprites on the border
 * area.
 *
 * The sprite attributes determine which sprite pattern the sprite should use,
 * the x and y position of the sprite, an optional sprite palette offset
 * (0 - 15, set to 0 if not used), a bit-mask of sprite flags (MIRROR_X_MASK,
 * MIRROR_Y_MASK, ROTATE_MASK) or 0 if not set, and whether or not the sprite
 * should be visible.
 *
 * After each call to set_sprite_attributes_ext(), the current sprite slot is
 * automatically incremented.
 */
void set_sprite_attributes_ext(uint8_t sprite_pattern_slot,
                               uint8_t x,
                               uint8_t y,
                               uint8_t palette_offset,
                               uint8_t sprite_flags,
                               bool visible);

#endif
