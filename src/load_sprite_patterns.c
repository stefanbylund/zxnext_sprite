/*******************************************************************************
 * Stefan Bylund 2017
 *
 * Implementation of load_sprite_patterns() in zxnext_sprite.h.
 ******************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <arch/zx/esxdos.h>
#include "zxnext_sprite.h"

void load_sprite_patterns(const char *filename,
                          const void *sprite_pattern_buf,
                          uint8_t num_sprite_patterns,
                          uint8_t start_sprite_pattern_slot)
{
    uint8_t filehandle;

    if ((filename == NULL) || (sprite_pattern_buf == NULL) ||
        (num_sprite_patterns == 0) || (start_sprite_pattern_slot > 63))
    {
        return;
    }

    if (start_sprite_pattern_slot + num_sprite_patterns > 64)
    {
        num_sprite_patterns = 64 - start_sprite_pattern_slot;
    }

    errno = 0;
    filehandle = esxdos_f_open(filename, ESXDOS_MODE_R | ESXDOS_MODE_OE);
    if (errno)
    {
        return;
    }

    set_sprite_slot(start_sprite_pattern_slot);

    while (num_sprite_patterns--)
    {
        esxdos_f_read(filehandle, (void *) sprite_pattern_buf, 256);
        if (errno)
        {
            break;
        }
        set_sprite_pattern(sprite_pattern_buf);
    }

    esxdos_f_close(filehandle);
}
