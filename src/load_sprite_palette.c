/*******************************************************************************
 * Stefan Bylund 2018
 *
 * Implementation of load_sprite_palette() in zxnext_sprite.h.
 ******************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnext_sprite.h"

void load_sprite_palette(const char *filename, const void *sprite_palette_buf)
{
    uint8_t filehandle;

    if ((filename == NULL) || (sprite_palette_buf == NULL))
    {
        return;
    }

    errno = 0;
    filehandle = esxdos_f_open(filename, ESXDOS_MODE_R | ESXDOS_MODE_OE);
    if (errno)
    {
        return;
    }

    esxdos_f_read(filehandle, (void *) sprite_palette_buf, 256);
    if (errno)
    {
        goto end;
    }
    set_sprite_palette((uint16_t *) sprite_palette_buf, 128, 0);

    esxdos_f_read(filehandle, (void *) sprite_palette_buf, 256);
    if (errno)
    {
        goto end;
    }
    set_sprite_palette((uint16_t *) sprite_palette_buf, 128, 128);

end:
    esxdos_f_close(filehandle);
}
