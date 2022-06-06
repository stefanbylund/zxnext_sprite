################################################################################
# Stefan Bylund 2017
#
# Makefile for compiling sprite demo program for ZX Spectrum Next.
# Supports both the SCCZ80 and SDCC compilers.
################################################################################

MKDIR := mkdir -p

RM := rm -rf

CP := cp

ZIP := zip -r -q

ZXNEXT_SPRITE := ..

ZXNEXT_SPRITE_INCLUDE := $(ZXNEXT_SPRITE)/include

ZXNEXT_SPRITE_LIB_SCCZ80 := $(ZXNEXT_SPRITE)/lib/sccz80

ZXNEXT_SPRITE_LIB_SDCC_IX := $(ZXNEXT_SPRITE)/lib/sdcc_ix

ZXNEXT_SPRITE_LIB_SDCC_IY := $(ZXNEXT_SPRITE)/lib/sdcc_iy

SRCS := src/zxnext_sprite_demo.c

BINDIR_SCCZ80 := bin/sccz80

BINDIR_SDCC_IX := bin/sdcc_ix

BINDIR_SDCC_IY := bin/sdcc_iy

DEBUGFLAGS := --list --c-code-in-asm

all: all_sccz80 all_sdcc_ix all_sdcc_iy

all_sccz80:
	$(MKDIR) $(BINDIR_SCCZ80)
	zcc +zxn -subtype=nex -vn -O3 -startup=31 -clib=new -m $(DEBUG) -L$(ZXNEXT_SPRITE_LIB_SCCZ80) -lzxnext_sprite -I$(ZXNEXT_SPRITE_INCLUDE) $(SRCS) -o $(BINDIR_SCCZ80)/zxnext_sprite_demo -create-app

all_sdcc_ix:
	$(MKDIR) $(BINDIR_SDCC_IX)
	zcc +zxn -subtype=nex -vn -SO3 -startup=31 -clib=sdcc_ix -m $(DEBUG) --max-allocs-per-node200000 -L$(ZXNEXT_SPRITE_LIB_SDCC_IX) -lzxnext_sprite -I$(ZXNEXT_SPRITE_INCLUDE) $(SRCS) -o $(BINDIR_SDCC_IX)/zxnext_sprite_demo -create-app

all_sdcc_iy:
	$(MKDIR) $(BINDIR_SDCC_IY)
	zcc +zxn -subtype=nex -vn -SO3 -startup=31 -clib=sdcc_iy -m $(DEBUG) --max-allocs-per-node200000 -L$(ZXNEXT_SPRITE_LIB_SDCC_IY) -lzxnext_sprite -I$(ZXNEXT_SPRITE_INCLUDE) $(SRCS) -o $(BINDIR_SDCC_IY)/zxnext_sprite_demo -create-app

debug_sccz80: DEBUG = $(DEBUGFLAGS)

debug_sdcc_ix: DEBUG = $(DEBUGFLAGS)

debug_sdcc_iy: DEBUG = $(DEBUGFLAGS)

debug_sccz80: all_sccz80

debug_sdcc_ix: all_sdcc_ix

debug_sdcc_iy: all_sdcc_iy

clean:
	$(RM) bin zcc_opt.def zcc_proj.lst src/*.lis
