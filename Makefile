################################################################################
# Stefan Bylund 2017
#
# Makefile for compiling C hardware sprite library for ZX Spectrum Next.
# Supports both the SCCZ80 and SDCC compilers.
################################################################################

MKDIR := mkdir -p

RM := rm -rf

CP := cp -r

ZIP := zip -r -q

SRCS := src/set_sprite_layers_system.c \
src/get_sprite_system_state.c \
src/set_sprite_display_palette.c \
src/set_sprite_rw_palette.c \
src/set_sprite_palette.c \
src/reset_sprite_palette.c \
src/set_sprite_slot.c \
src/set_sprite_pattern.c \
src/set_sprite_attributes.c \
src/set_sprite_attributes_ext.c \
src/load_sprite_patterns.c \
src/load_sprite_palette.c

LIBDIR_SCCZ80 := lib/sccz80

LIBDIR_SDCC_IX := lib/sdcc_ix

LIBDIR_SDCC_IY := lib/sdcc_iy

DEBUGFLAGS := --list --c-code-in-asm

all: all_sccz80 all_sdcc_ix all_sdcc_iy

all_sccz80:
	$(MKDIR) $(LIBDIR_SCCZ80)
	zcc +zxn -vn -O3 -x -clib=new $(DEBUG) -Iinclude $(SRCS) -o $(LIBDIR_SCCZ80)/zxnext_sprite

all_sdcc_ix:
	$(MKDIR) $(LIBDIR_SDCC_IX)
	zcc +zxn -vn -SO3 -x -clib=sdcc_ix $(DEBUG) --max-allocs-per-node200000 -Iinclude $(SRCS) -o $(LIBDIR_SDCC_IX)/zxnext_sprite

all_sdcc_iy:
	$(MKDIR) $(LIBDIR_SDCC_IY)
	zcc +zxn -vn -SO3 -x -clib=sdcc_iy $(DEBUG) --max-allocs-per-node200000 -Iinclude $(SRCS) -o $(LIBDIR_SDCC_IY)/zxnext_sprite

debug_sccz80: DEBUG = $(DEBUGFLAGS)

debug_sdcc_ix: DEBUG = $(DEBUGFLAGS)

debug_sdcc_iy: DEBUG = $(DEBUGFLAGS)

debug_sccz80: all_sccz80

debug_sdcc_ix: all_sdcc_ix

debug_sdcc_iy: all_sdcc_iy

distro:
	# Create general distro
	$(RM) build/zxnext_sprite.zip
	cd ..; $(ZIP) zxnext_sprite/build/zxnext_sprite.zip zxnext_sprite/include zxnext_sprite/lib
	# Create distro for z88dk-lib tool
	$(RM) tmp
	$(MKDIR) tmp/zxnext_sprite/zxn/include/newlib
	$(MKDIR) tmp/zxnext_sprite/zxn/lib/newlib
	$(CP) include/* tmp/zxnext_sprite/zxn/include/newlib
	$(CP) lib/sccz80 tmp/zxnext_sprite/zxn/lib/newlib
	$(CP) lib/sdcc_ix tmp/zxnext_sprite/zxn/lib/newlib
	$(CP) lib/sdcc_iy tmp/zxnext_sprite/zxn/lib/newlib
	$(RM) build/zxnext_sprite_z88dk.zip
	cd tmp; $(ZIP) ../build/zxnext_sprite_z88dk.zip zxnext_sprite
	$(RM) tmp

clean:
	$(RM) lib tmp zcc_opt.def zcc_proj.lst src/*.lis
