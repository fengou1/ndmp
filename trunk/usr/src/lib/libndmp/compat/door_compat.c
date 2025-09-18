#include "door.h"

#ifndef __sun
#include <errno.h>

int
door_call(int fd, door_arg_t *arg)
{
        (void)fd;
        (void)arg;
        errno = ENOTSUP;
        return (-1);
}

#endif /* __sun */
