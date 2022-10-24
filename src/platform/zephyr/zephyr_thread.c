//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// Zephyr threads.

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_ZEPHYR

// #include <errno.h>
// #include <fcntl.h>
// #include <signal.h>
// #include <stdlib.h>
#include <string.h>
#include <core/panic.h>
// #include <sys/types.h>
// #include <time.h>
// #include <unistd.h>

static volatile int nni_plat_inited = 0;
static int          nni_plat_forked = 0;

void
nni_plat_mtx_init(nni_plat_mtx *mtx)
{
	k_mutex_init(&mtx->mtx);
}

void
nni_plat_mtx_fini(nni_plat_mtx *mtx)
{
	(void) mtx;
	// NOOP
}

void
nni_plat_mtx_lock(nni_plat_mtx *mtx)
{
	k_mutex_lock(&mtx->mtx, K_FOREVER);
}

void
nni_plat_mtx_unlock(nni_plat_mtx *mtx)
{
	k_mutex_unlock(&mtx->mtx);
}

void
nni_rwlock_init(nni_rwlock *rwl)
{
	k_mutex_init(&rwl->mtx);
}

void
nni_rwlock_fini(nni_rwlock *rwl)
{
	(void) rwl;
	// NOOP
}

void
nni_rwlock_rdlock(nni_rwlock *rwl)
{
	k_mutex_lock(&rwl->mtx, K_FOREVER);
}

void
nni_rwlock_wrlock(nni_rwlock *rwl)
{
	k_mutex_lock(&rwl->mtx, K_FOREVER);
}

void
nni_rwlock_unlock(nni_rwlock *rwl)
{
	k_mutex_unlock(&rwl->mtx);
}

void
nni_plat_cv_init(nni_plat_cv *cv, nni_plat_mtx *mtx)
{
	k_condvar_init(&cv->cv);
	cv->mtx = mtx;
}

void
nni_plat_cv_wake(nni_plat_cv *cv)
{
	k_condvar_broadcast(&cv->cv);
}

void
nni_plat_cv_wake1(nni_plat_cv *cv)
{
	k_condvar_signal(&cv->cv);
}

void
nni_plat_cv_wait(nni_plat_cv *cv)
{
	k_condvar_wait(&cv->cv, &cv->mtx->mtx, K_FOREVER);
}

int
nni_plat_cv_until(nni_plat_cv *cv, nni_time until)
{
	nni_time now = nni_clock();
	nni_duration diff = until - now;

	k_timeout_t timeout;

	if (diff < 0)
	{
		timeout = K_MSEC(diff);
	}
	else
	{
		timeout = K_NO_WAIT;
	}

	return k_condvar_wait(&cv->cv, &cv->mtx->mtx, timeout);
}

void
nni_plat_cv_fini(nni_plat_cv *cv)
{
	// NOOP
	cv->mtx = NULL;
}

static void
nni_plat_thr_main(void *arg, void *, void *)
{
	nni_plat_thr *thr = arg;
	thr->func(thr->arg);
}

static K_THREAD_STACK_ARRAY_DEFINE(stack_area, NNG_MAX_THREADS, NNG_THREAD_STACK_SIZE);
static int allocated_threads = 0;

int
nni_plat_thr_init(nni_plat_thr *thr, void (*fn)(void *), void *arg)
{
	thr->func = fn;
	thr->arg  = arg;

	if (allocated_threads >= NNG_MAX_THREADS)
	{
		nni_panic("Cannot allocate more than %d threads", NNG_MAX_THREADS);
	}

	thr->tid = k_thread_create(&thr->thr, stack_area[allocated_threads++],
	    NNG_THREAD_STACK_SIZE, (k_thread_entry_t) nni_plat_thr_main, thr,
	    NULL, NULL, K_PRIO_COOP(NNG_THREAD_PRIORITY), 0, K_NO_WAIT);

	return (0);
}

void
nni_plat_thr_fini(nni_plat_thr *thr)
{
	int rv;

	if ((rv = k_thread_join(&thr->thr, K_FOREVER))) {
		nni_panic("pthread_join: %s", strerror(rv));
	}
}

bool
nni_plat_thr_is_self(nni_plat_thr *thr)
{
	return (k_current_get() == thr->tid);
}

void
nni_plat_thr_set_name(nni_plat_thr *thr, const char *name)
{
	k_thread_name_set(thr->tid, name);
}

void
nni_atfork_child(void)
{
	nni_plat_forked = 1;
}

int
nni_plat_init(int (*helper)(void))
{
	int rv;

	if (nni_plat_forked) {
		nni_panic("nng is not fork-reentrant safe");
	}
	if (nni_plat_inited) {
		return (0); // fast path
	}

	if ((rv = nni_posix_pollq_sysinit()) != 0) {
		return (rv);
	}

	if ((rv = nni_posix_resolv_sysinit()) != 0) {
		nni_posix_pollq_sysfini();
		return (rv);
	}

	if ((rv = helper()) == 0) {
		nni_plat_inited = 1;
	}

	return rv;
}

void
nni_plat_fini(void)
{
}

int
nni_plat_ncpu(void)
{
#ifdef CONFIG_MP_NUM_CPUS
	return (CONFIG_MP_NUM_CPUS);
#else
	return (1);
#endif
}

#endif // NNG_PLATFORM_ZEPHYR
