/*******************************************************************************
 * Stefan Bylund 2017
 *
 * C definitions of the I/O port register system of the Sinclair ZX Spectrum
 * Next as specified at http://www.specnext.com/tbblue-io-port-system/. These
 * registers are used for reading and writing information about the hardware and
 * settings.
 *
 * The letters (R), (W) and (R/W) indicates if a register is only readable, only
 * writable or both readable/writable.
 *
 * Some registers are accessible only during the initialization process (IPL
 * and modules).
 ******************************************************************************/

#ifndef _ZXNEXT_REGISTERS_H
#define _ZXNEXT_REGISTERS_H

/*
 * Output port used to set the 8-bit registry number as listed below.
 */
#define REGISTER_NUMBER_PORT 0x243B

/*
 * Input/output port used to read/write the 8-bit registry value of the registry
 * number set.
 */
#define REGISTER_VALUE_PORT 0x253B

/*
 * (R) Machine ID (http://www.specnext.com/hardware-ids/):
 *  1 = Terasic Altera DE-1
 *  2 = Terasic Altera DE-2
 *  5 = FBLabs
 *  6 = VTrucco
 *  7 = WXEDA
 *  8 = Emulators
 *  9 = ZX-Uno
 * 10 = Sinclair ZX Spectrum Next
 * 11 = Multicore
 */
#define MACHINE_ID_REGISTER 0

/*
 * (R) Version:
 * bits 7-4 = major version
 * bits 3-0 = minor version
 */
#define VERSION_REGISTER 1

/*
 * (R/W) Reset:
 * bits 7-3 = Reserved, must be 0
 * bit 2 = (R) Power-on reset (PoR)
 * bit 1 = (R/W) Reading 1 indicates a hard reset. Writing 1 causes a hard reset.
 * bit 0 = (R/W) Reading 1 indicates a soft reset. Writing 1 causes a soft reset.
 */
#define RESET_REGISTER 2

/*
 * (W) Set machine type (only in IPL or config mode):
 * Writing this register disables the IPL (0x0000-0x3FFF are mapped to the RAM
 * instead of the internal ROM).
 * bit 7 = Lock timing
 * bits 6-4 = Timing:
 *   000/001 = ZX 48K
 *   010 = ZX 128K
 *   011 = ZX +2/+3e
 *   100 = Pentagon 128K
 * bit 3 = Reserved, must be 0
 * bits 2-0 = Machine type:
 *   000 = Config mode
 *   001 = ZX 48K
 *   010 = ZX 128K
 *   011 = ZX +2/+3e
 *   100 = Pentagon 128K
 */
#define MACHINE_TYPE_REGISTER 3

/*
 * (W) Set page RAM (only in config mode, not IPL):
 * bits 7-6 = Reserved, must be 0
 * bits 5-0 = RAM page mapped in 0x0000-0x3FFF (64 pages of 16K = 1024K). Reset to 0 after a PoR or hard reset.
 */
#define PAGE_RAM_REGISTER 4

/*
 * (R/W) Peripheral 1 settings:
 * bits 7-6 = joystick 1 mode (00 = Sinclair, 01 = Kempston, 10 = Cursor). Reset to 0 after a PoR or hard reset.
 * bits 5-4 = joystick 2 mode (00 = Sinclair, 01 = Kempston, 10 = Cursor). Reset to 0 after a PoR or hard reset.
 * bit 3 = Reserved, must be 0.
 * bit 2 = 50/60 Hz mode (0 = 50 Hz, 1 = 60 Hz). Reset to 0 after a PoR or hard reset.
 * bit 1 = Enable scanlines (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 0 = Enable scandoubler (1 = enabled). Reset to 1 after a PoR or hard reset.
 */
#define PERIPHERAL_1_REGISTER 5

/*
 * (R/W) Peripheral 2 settings:
 * bit 7 = Enable turbo mode (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 6 = DAC chip mode (0 = I2S, 1 = JAP) (Only on VTrucco board). Reset to 0 after a PoR or hard reset.
 * bit 5 = Enable lightpen (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 4 = Enable DivMMC (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 3 = Enable Multiface (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 2 = PS/2 mode (0 = keyboard, 1 = mouse). Reset to 0 after a PoR or hard reset.
 * bits 1-0 = Audio chip mode (0- = disabled, 10 = YM, 11 = AY)
 */
#define PERIPHERAL_2_REGISTER 6

/*
 * (R/W) Turbo mode:
 * bits 7-2 = Reserved, must be 0
 * bits 1-0 = Turbo mode. Reset to 00 after a PoR or hard reset.
 *   00 = 3.5 MHz
 *   01 = 7 MHz
 *   10 = 14 MHz
 *   11 = 28 MHz
 */
#define TURBO_MODE_REGISTER 7

/*
 * (R/W) Peripheral 3 settings:
 * bits 7-6 = Reserved, must be 0
 * bit 5 = Stereo mode (0 = ABC, 1 = ACB). Reset to 0 after a PoR or hard reset.
 * bit 4 = Enable internal speaker (1 = enabled). Reset to 1 after a PoR or hard reset.
 * bit 3 = Enable Specdrum/Covox (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 2 = Enable Timex modes (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 1 = Enable TurboSound (1 = enabled). Reset to 0 after a PoR or hard reset.
 * bit 0 = Reserved, must be 0.
 */
#define PERIPHERAL_3_REGISTER 8

/*
 * (R/W) Anti-brick system (only on Sinclair ZX Spectrum Next board):
 * bit 7 = (W) If 1 start normal core
 * bits 6-2 = Reserved, must be 0
 * bit 1 = (R) Button DivMMC (1 = pressed)
 * bit 0 = (R) Button Multiface (1 = pressed)
 */
#define ANTI_BRICK_SYSTEM_REGISTER 10

/*
 * (R/W) Layer 2 RAM page:
 * bits 7-6 = Reserved, must be 0
 * bits 5-0 = SRAM page, points to page 8 after a reset which means page 8, 9 and 10.
 */
#define LAYER2_RAM_PAGE_REGISTER 18

/*
 * (R/W) Layer 2 shadow RAM page:
 * bits 7-6 = Reserved, must be 0
 * bits 5-0 = SRAM page, points to page 11 after a reset which means page 11, 12 and 13.
 */
#define LAYER2_SHADOW_RAM_PAGE_REGISTER 19

/*
 * (R/W) Global transparency colour:
 * bits 7-0 = Transparency colour value. Reset to 0xE3 after a reset.
 */
#define GLOBAL_TRANSPARENCY_COLOR_REGISTER 20

/*
 * (R/W) Sprite and layers system:
 * bit 7 = LoRes mode, 128 x 96 pixels with 256 colours (1 = enabled).
 * bits 6-5 = Reserved, must be 0
 * bits 4-2 = Set layer priorities; S=sprites, L=layer 2 screen, U=ULA screen.
 * Reset default is 000, sprites over layer 2 screen over ULA screen.
 *   000 = S L U
 *   001 = L S U
 *   010 = S U L
 *   011 = L U S
 *   100 = U S L
 *   101 = U L S
 * bit 1 = Sprites on border (1 = yes). Reset to 0 after a reset.
 * bit 0 = Sprites visible (1 = visible). Reset to 0 after a reset.
 */
#define SPRITE_LAYERS_SYSTEM_REGISTER 21

/*
 * (R/W) Layer 2 offset x:
 * bits 7-0 = X offset (0-255). Reset to 0 after a reset.
 */
#define LAYER2_OFFSET_X_REGISTER 22

/*
 * (R/W) Layer 2 offset y:
 * bits 7-0 = Y offset (0-191). Reset to 0 after a reset.
 */
#define LAYER2_OFFSET_Y_REGISTER 23

/*
 * (R) Active video line (MSB):
 * bits 7-1 = Reserved, always 0
 * bit 0 = Active line MSB. Reset to 0 after a reset.
 */
#define ACTIVE_VIDEO_LINE_MSB_REGISTER 30

/*
 * (R) Active video line (LSB):
 * bits 7-0 = Active line LSB (0-255). Reset to 0 after a reset.
 */
#define ACTIVE_VIDEO_LINE_LSB_REGISTER 31

/*
 * (R/W) Line interrupt control:
 * bit 7 = (R) INT flag, 1 = During INT (even if the CPU has interrupt disabled)
 * bits 6-3 = Reserved, must be 0
 * bit 2 = If 1 disables original ULA interrupt. Reset to 0 after a reset.
 * bit 1 = If 1 enables line interrupt. Reset to 0 after a reset.
 * bit 0 = Line interrupt line value MSB. Reset to 0 after a reset.
 */
#define LINE_INTERRUPT_CONTROL_REGISTER 34

/*
 * (R/W) Line interrupt value LSB:
 * bits 7-0 = Line interrupt line value LSB (0-255). Reset to 0 after a reset.
 */
#define LINE_INTERRUPT_VALUE_LSB_REGISTER 35

/*
 * (W) High address of keymap:
 * bits 7-1 = Reserved, must be 0
 * bit 0 = MSB address
 */
#define KEYMAP_HIGH_ADDRESS_REGISTER 40

/*
 * (W) Low address of keymap:
 * bits 7-0 = LSB address
 */
#define KEYMAP_LOW_ADDRESS_REGISTER 41

/*
 * (W) High data to keymap:
 * bits 7-1 = Reserved, must be 0
 * bit 0 = MSB data
 */
#define KEYMAP_HIGH_DATA_REGISTER 42

/*
 * (W) Low data to keymap (when writing this register, the address is auto-incremented):
 * bits 7-0 = LSB data
 */
#define KEYMAP_LOW_DATA_REGISTER 43

/*
 * (R/W) LoRes offset x:
 * bits 7-0 = X offset (0-255). Reset to 0 after a reset.
 * Being only 128 pixels, this allows the display to scroll in "half-pixels",
 * at the same resolution and smoothness as layer 2.
 */
#define LORES_OFFSET_X_REGISTER 50

/*
 * (R/W) LoRes offset y:
 * bits 7-0 = Y offset (0-191). Reset to 0 after a reset.
 * Being only 96 pixels, this allows the display to scroll in "half-pixels",
 * at the same resolution and smoothness as layer 2.
 */
#define LORES_OFFSET_Y_REGISTER 51

/*
 * (W) Palette index:
 * bits 7-0 = Select the palette index (0-255) to change the default colour for.
 * Indexes 0 to 127 are for ink colours and indexes 128 to 255 are for paper
 * colours (except in full ink colour mode, where all indexes 0 to 255 are ink
 * colours except index 128 which is the paper colour). Border colours are the
 * same as the paper colours 0 to 7, indexes 128 to 135, even in full ink colour
 * mode.
 */
#define PALETTE_INDEX_REGISTER 64

/*
 * (W) Palette value:
 * bits 7-0 = Colour for the palette index selected by the register
 * PALETTE_INDEX_REGISTER. Format is RRRGGGBB.
 * After a write, the palette index is auto-incremented to the next index.
 * The changed palette remains until a hard reset.
 */
#define PALETTE_VALUE_REGISTER 65

/*
 * (W) Palette format:
 * bits 7-0 = Index of the last ink colour entry in the palette. Reset to 15 after a reset.
 * This number can be 1, 3, 7, 15, 31, 63, 127 or 255. The value 255 enables the
 * full ink colour mode where all the palette entries are ink colours except
 * index 128 which is the paper colour.
 */
#define PALETTE_FORMAT_REGISTER 66

/*
 * (W) Palette control:
 * bits 7-2 = Reserved, must be 0
 * bit 1 = Select the second palette.
 * bit 0 = Disable the standard Spectrum flash feature to enable the extra colours.
 * Reset to 0 after a reset.
 */
#define PALETTE_CONTROL_REGISTER 67

/*
 * (W) Palette value lower bit:
 * bits 7-1 = Reserved, must be 0
 * bit 0 = Set the lower blue bit colour for the current palette value.
 */
#define PALETTE_VALUE_LSB_REGISTER 68

/*
 * (W) Debug LEDs (DE-1, DE-2 and Multicore boards only)
 */
#define DEBUG_LEDS_REGISTER 255

#endif
