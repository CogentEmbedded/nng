//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef PLATFORM_POSIX_IMPL_H
#define PLATFORM_POSIX_IMPL_H

#if defined(__ZEPHYR__)
#include "platform/posix/zephyr_config.h"
#else
#include "platform/posix/posix_config.h"
#endif

#ifdef NNG_PLATFORM_POSIX_SOCKADDR
#include <sys/socket.h>
extern int    nni_posix_sockaddr2nn(nni_sockaddr *, const void *, size_t);
extern size_t nni_posix_nn2sockaddr(void *, const nni_sockaddr *);
#endif

#ifdef NNG_PLATFORM_POSIX_DEBUG
extern int nni_plat_errno(int);

#endif

// Define types that this platform uses.
#ifdef NNG_PLATFORM_POSIX_THREAD

#include <pthread.h>

#ifndef PTHREAD_MUTEX_INITIALIZER
#define PTHREAD_MUTEX_INITIALIZER {}
#endif

#ifndef PTHREAD_COND_INITIALIZER
#define PTHREAD_COND_INITIALIZER {}
#endif

#ifndef PTHREAD_RWLOCK_INITIALIZER
#define PTHREAD_RWLOCK_INITIALIZER {}
#endif

// These types are provided for here, to permit them to be directly inlined
// elsewhere.

struct nni_plat_mtx {
	pthread_mutex_t mtx;
};

#define NNI_MTX_INITIALIZER               \
	{                                 \
		PTHREAD_MUTEX_INITIALIZER \
	}

struct nni_rwlock {
	pthread_rwlock_t rwl;
};

#define NNI_RWLOCK_INITIALIZER             \
	{                                  \
		PTHREAD_RWLOCK_INITIALIZER \
	}

// No static form of CV initialization because of the need to use
// attributes to set the clock type.
struct nni_plat_cv {
	pthread_cond_t cv;
	nni_plat_mtx  *mtx;
};

// NOTE: condition variables initialized with this should *NOT*
// be used with nni_cv_until -- the clock attributes are not passed
// and the wake-up times will not be correct.
#define NNI_CV_INITIALIZER(mxp)                            \
	{                                                  \
		.mtx = mxp, .cv = PTHREAD_COND_INITIALIZER \
	}

struct nni_plat_thr {
	pthread_t tid;
	void (*func)(void *);
	void *arg;
};

struct nni_plat_flock {
	int fd;
};

#define NNG_PLATFORM_DIR_SEP "/"

#ifdef NNG_HAVE_STDATOMIC
#include <stdatomic.h>

struct nni_atomic_flag {
	atomic_flag f;
};

struct nni_atomic_int {
	atomic_int v;
};

struct nni_atomic_u64 {
	atomic_uint_fast64_t v;
};

struct nni_atomic_bool {
	atomic_bool v;
};

struct nni_atomic_ptr {
	atomic_uintptr_t v;
};

#elif defined(__ZEPHYR__)

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

#else // NNG_HAVE_C11_ATOMIC
struct nni_atomic_flag {
	bool f;
};

struct nni_atomic_bool {
	bool b;
};

struct nni_atomic_int {
	int v;
};

struct nni_atomic_u64 {
	uint64_t v;
};

struct nni_atomic_ptr {
	void *v;
};

#endif

#endif

extern int  nni_posix_pollq_sysinit(void);
extern void nni_posix_pollq_sysfini(void);
extern int  nni_posix_resolv_sysinit(void);
extern void nni_posix_resolv_sysfini(void);

#endif // PLATFORM_POSIX_IMPL_H
