#ifndef _LIBNDMP_COMPAT_DOOR_H
#define _LIBNDMP_COMPAT_DOOR_H

#ifdef __sun
#include_next <door.h>
#else
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

typedef struct door_desc {
        int d_descriptor;
} door_desc_t;

typedef struct door_arg {
        char *data_ptr;
        size_t data_size;
        char *rbuf;
        size_t rsize;
        door_desc_t *desc_ptr;
        unsigned int desc_num;
} door_arg_t;

int door_call(int, door_arg_t *);

#endif /* __sun */

#endif /* _LIBNDMP_COMPAT_DOOR_H */
