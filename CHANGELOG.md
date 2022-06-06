# Changelog

All notable changes to the C Hardware Sprite API (zxnext_sprite)
for Spectrum Next will be documented in this file.

## 2022-06-06

* Moved the zxnext_sprite_demo repository into this repository's demo folder.

## 2018-05-03

* Added support for the z88dk-lib tool.

## 2018-01-20

* Added macros for getting/setting the global transparency colour.
* Added support for sprite palette with 9-bit colour values.

## 2017-09-18

* Used intrinsic_outi() in set_sprite_pattern.c.
* Added load_sprite_patterns() function.

## 2017-09-04

* Updated set_sprite_layers_system() function.

## 2017-08-17

* Updated set_sprite_pattern() to work in CSpect.

## 2017-07-25

* Changed sprite pattern port from 0x55 to 0x5B, use otir in set_sprite_pattern().

## 2017-07-23

* Updated API with new sprites / layer 2 / ULA layer priorities feature.

## 2017-07-19

* Added missing include guard in header file.

## 2017-07-15

* Used otir when setting palette and declared port 0x57 as an 8-bit port.

## 2017-07-02

* First public release.
