//
// Copyright 2021-2022 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// Some dependency notes:
//
// NNG_PLATFORM_POSIX_THREAD depends on NNG_PLATFORM_POSIX_CLOCK.  Also,
// when using NNG_PLATFORM_POSIX_CLOCK, your condition variable timeouts need
// to use the same base clock values.  Normally these should be used
// together.  Almost everything depends on NNG_PLATFORM_POSIX_DEBUG.
#ifdef NNG_PLATFORM_POSIX
#define NNG_PLATFORM_POSIX_ALLOC
#define NNG_PLATFORM_POSIX_DEBUG
#define NNG_PLATFORM_POSIX_CLOCK

#define NNG_PLATFORM_POSIX_TCP
#define NNG_PLATFORM_POSIX_PIPE
#define NNG_PLATFORM_POSIX_RANDOM
#define NNG_PLATFORM_POSIX_SOCKET
#define NNG_PLATFORM_POSIX_THREAD
#define NNG_PLATFORM_POSIX_PIPEDESC
#define NNG_PLATFORM_POSIX_EPDESC
#define NNG_PLATFORM_POSIX_SOCKADDR


#endif

#ifdef NNG_PLATFORM_POSIX

#include <zephyr/posix/time.h>

#define NNG_HAVE_CLOCK_GETTIME
#define NNG_USE_CLOCKID CLOCK_MONOTONIC

#define NNG_USE_POSIX_RESOLV_GAI 1
#define NNG_RESOLV_CONCURRENCY 1

#ifndef NNG_THREAD_STACK_SIZE
#define NNG_THREAD_STACK_SIZE 2048
#endif
#ifndef NNG_THREAD_PRIORITY
#define NNG_THREAD_PRIORITY 5
#endif
#define NNG_THREAD_ALLOC_STACK

// TODO make it depend on CONFIG_EVENTFD
#define NNG_USE_EVENTFD

// This is required for posix_resolv_gai.c
#define EAI_MEMORY DNS_EAI_MEMORY
#define EAI_SYSTEM DNS_EAI_SYSTEM
#define EAI_NONAME DNS_EAI_NONAME
#define EAI_NODATA DNS_EAI_NODATA
#define EAI_SERVICE DNS_EAI_SERVICE
#define EAI_BADFLAGS DNS_EAI_BADFLAGS
#define EAI_SOCKTYPE DNS_EAI_SOCKTYPE
#define EAI_CANCELED DNS_EAI_CANCELED
#define EAI_AGAIN DNS_EAI_AGAIN

#include <sys/socket.h>
#include <unistd.h>

static inline ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
{
	ssize_t ret = 0;

	for (int i = 0; i < iovcnt; i++)
    {
		ssize_t r = read(fd, iov[i].iov_base, iov[i].iov_len);

		if (r < 0) {
			return r;
	    }

	    ret += r;
	}

	return ret;
}

#endif // NNG_PLATFORM_POSIX
