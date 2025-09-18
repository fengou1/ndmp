#ifndef _LIBNDMP_COMPAT_THREAD_H
#define _LIBNDMP_COMPAT_THREAD_H

#ifdef __sun
#include_next <thread.h>
#else
#include <pthread.h>

typedef pthread_t thread_t;

#endif /* __sun */

#endif /* _LIBNDMP_COMPAT_THREAD_H */
