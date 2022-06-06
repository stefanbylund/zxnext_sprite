/*******************************************************************************
 * Stefan Bylund 2017
 *
 * A simple sprite demo program for ZX Spectrum Next.
 *
 * zcc +zxn -subtype=nex -vn -SO3 -startup=31 -clib=sdcc_iy
 *   --max-allocs-per-node200000 -L<zxnext_sprite>/lib/sdcc_iy -lzxnext_sprite
 *   -I<zxnext_sprite>/include zxnext_sprite_demo.c -o zxnext_sprite_demo -create-app
 ******************************************************************************/

#include <arch/zxn.h>
#include <input.h>
#include <z80.h>
#include <intrinsic.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "zxnext_sprite.h"

#pragma output CRT_ORG_CODE = 0x8184
#pragma output REGISTER_SP = 0xFF58
#pragma output CLIB_MALLOC_HEAP_SIZE = 0
#pragma output CLIB_STDIO_HEAP_SIZE = 0
#pragma output CLIB_FOPEN_MAX = -1

/*
 * Define IDE_FRIENDLY in your C IDE to disable Z88DK C extensions and avoid
 * parser errors/warnings in the IDE. Do NOT define IDE_FRIENDLY when compiling
 * the code with Z88DK.
 */
#ifdef IDE_FRIENDLY
#define __z88dk_fastcall
#define __preserves_regs(...)
#endif

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

static void init_hardware(void);

static void init_isr(void);

static void create_background(void);

static void create_sprites(void);

static void update_sprites(void);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/

typedef struct sprite_info {
    uint8_t x; // X coordinate in pixels
    uint8_t y; // Y coordinate in pixels
    int8_t dx; // Horizontal displacement in pixels
    int8_t dy; // Vertical displacement in pixels
} sprite_info_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

static const uint8_t sprite_pattern[] =
{
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFB, 0xFB, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFB, 0xF5, 0xF5, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFB, 0xF5, 0xA8, 0xA8, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0xFF, 0xFF, 0xFB, 0xA8, 0x44, 0xA8, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0x04, 0x04, 0x04, 0xFF, 0xFB, 0xA8, 0x44, 0xA8, 0xFB, 0xFF, 0x04, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0xA8, 0x44, 0x44, 0xFB, 0xFF, 0x04, 0xE3, 0x04, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0x44, 0x44, 0x44, 0xFB, 0xFF, 0x04, 0x4D, 0x04, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0x44, 0x44, 0x44, 0x44, 0xFA, 0x4D, 0x04, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0xFB, 0x44, 0xFF, 0xF5, 0x44, 0x04, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFF, 0x44, 0xF5, 0xA8, 0x04, 0xE3, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0xFA, 0x44, 0x04, 0xA8, 0x04, 0xE3, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0x4D, 0x4D, 0x04, 0xE3, 0x04, 0xF5, 0x04, 0xE3,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0x04, 0xE3, 0xE3, 0xE3, 0x04, 0xFA, 0x04,
    0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0x04, 0x04
};

static sprite_info_t sprite = {120, 88, 1, 1};

/*******************************************************************************
 * Functions
 ******************************************************************************/

static void init_hardware(void)
{
    // Put Z80 in 28 MHz turbo mode.
    ZXN_NEXTREG(REG_TURBO_MODE, 0x03);

    // Disable RAM memory contention.
    ZXN_NEXTREGA(REG_PERIPHERAL_3, ZXN_READ_REG(REG_PERIPHERAL_3) | RP3_DISABLE_CONTENTION);
}

static void init_isr(void)
{
    // Set up IM2 interrupt service routine:
    // Put Z80 in IM2 mode with a 257-byte interrupt vector table located
    // at 0x8000 (before CRT_ORG_CODE) filled with 0x81 bytes. Install an
    // empty interrupt service routine at the interrupt service routine
    // entry at address 0x8181.

    intrinsic_di();
    im2_init((void *) 0x8000);
    memset((void *) 0x8000, 0x81, 257);
    z80_bpoke(0x8181, 0xFB);
    z80_bpoke(0x8182, 0xED);
    z80_bpoke(0x8183, 0x4D);
    intrinsic_ei();
}

static void create_background(void)
{
    zx_border(INK_YELLOW);
    zx_cls(BRIGHT | INK_BLACK | PAPER_WHITE);
}

static void create_sprites(void)
{
    set_sprite_slot(0);
    set_sprite_pattern(sprite_pattern);

    set_sprite_slot(0);
    set_sprite_attributes_ext(0, sprite.x, sprite.y, 0, 0, true);
}

static void update_sprites(void)
{
    // Calculate next position of sprite.
    sprite.x += sprite.dx;
    sprite.y += sprite.dy;

    // If sprite is at the edge of the screen then change its direction.
    if ((sprite.x == 0) || (sprite.x >= 240))
    {
        sprite.dx = -sprite.dx;
    }
    if ((sprite.y == 0) || (sprite.y >= 176))
    {
        sprite.dy = -sprite.dy;
    }

    // Update sprite position.
    set_sprite_slot(0);
    set_sprite_attributes_ext(0, sprite.x, sprite.y, 0, 0, true);
}

int main(void)
{
    init_hardware();
    init_isr();
    create_background();
    create_sprites();
    set_sprite_layers_system(true, false, LAYER_PRIORITIES_S_L_U, false);

    while (true)
    {
        if (in_inkey() != 0)
        {
            break;
        }

        // Wait for vertical blanking interval.
        intrinsic_halt();

        update_sprites();
    }

    // Trig a soft reset. The Next hardware registers and I/O ports will be reset by NextZXOS after a soft reset.
    ZXN_NEXTREG(REG_RESET, RR_SOFT_RESET);
    return 0;
}
