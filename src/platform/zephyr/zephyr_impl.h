//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef PLATFORM_ZEPHYR_IMPL_H
#define PLATFORM_ZEPHYR_IMPL_H

#include <zephyr/kernel.h>

#include "platform/zephyr/zephyr_config.h"

extern int nni_plat_errno(int);

#include <zephyr/posix/sys/socket.h>
extern int    nni_posix_sockaddr2nn(nni_sockaddr *, const void *, size_t);
extern size_t nni_posix_nn2sockaddr(void *, const nni_sockaddr *);

// Define types that this platform uses.

/* Mutex as defined at
   https://docs.zephyrproject.org/3.2.0/kernel/services/synchronization/mutexes.html */
struct nni_plat_mtx {
	struct k_mutex mtx;
};

#define NNI_MTX_INITIALIZER {}

/* Zephyr has no rwlock support so use mutex as defined at
   https://docs.zephyrproject.org/3.2.0/reference/kernel/synchronization/mutexes.html */
struct nni_rwlock {
	struct k_mutex mtx;
};

#define NNI_RWLOCK_INITIALIZER {}

/* Condition variable as defined at
   https://docs.zephyrproject.org/3.2.0/reference/kernel/synchronization/condvar.html */
struct nni_plat_cv {
	struct k_condvar cv;
	nni_plat_mtx    *mtx;
};

#define NNI_CV_INITIALIZER(mxp) \
	{                           \
		.mtx = mxp,             \
	}

/* Thread as defined at
   https://docs.zephyrproject.org/3.2.0/reference/kernel/threads/index.html */
struct nni_plat_thr {
	struct k_thread thr;
	k_tid_t         tid;
	void (*func)(void *);
	void *arg;
};

/* Atomics as defined at
   https://docs.zephyrproject.org/3.2.0/kernel/services/other/atomic.html */
struct nni_atomic_flag {
	atomic_t f;
};

struct nni_atomic_bool {
	atomic_t b;
};

struct nni_atomic_int {
	atomic_t v;
};

struct nni_atomic_u64 {
	/* XXXX a 32-bit value is used instead. Should be enough
	        for storing file descriptors on an embedded system */
	atomic_t v;
};

struct nni_atomic_ptr {
	atomic_ptr_t v;
};

extern int  nni_posix_pollq_sysinit(void);
extern void nni_posix_pollq_sysfini(void);
extern int  nni_posix_resolv_sysinit(void);
extern void nni_posix_resolv_sysfini(void);

#endif // PLATFORM_ZEPHYR_IMPL_H
