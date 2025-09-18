#ifndef _LIBNDMP_COMPAT_SYNCH_H
#define _LIBNDMP_COMPAT_SYNCH_H

#ifdef __sun
#include_next <synch.h>
#else
#include <pthread.h>

typedef pthread_mutex_t mutex_t;

typedef pthread_mutexattr_t mutexattr_t;

typedef pthread_cond_t cond_t;

typedef pthread_condattr_t condattr_t;

#define DEFAULTMUTEX PTHREAD_MUTEX_INITIALIZER
#define DEFAULTCV    PTHREAD_COND_INITIALIZER

static inline int
mutex_lock(mutex_t *m)
{
        return (pthread_mutex_lock(m));
}

static inline int
mutex_unlock(mutex_t *m)
{
        return (pthread_mutex_unlock(m));
}

static inline int
mutex_init(mutex_t *m, int type, void *arg)
{
        (void)type;
        (void)arg;
        return (pthread_mutex_init(m, NULL));
}

static inline int
mutex_destroy(mutex_t *m)
{
        return (pthread_mutex_destroy(m));
}

#endif /* __sun */

#endif /* _LIBNDMP_COMPAT_SYNCH_H */
