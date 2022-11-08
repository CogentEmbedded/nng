//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
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
#define NNG_PLATFORM_POSIX_IPC
#define NNG_PLATFORM_POSIX_TCP
#define NNG_PLATFORM_POSIX_PIPE
#define NNG_PLATFORM_POSIX_RANDOM
#define NNG_PLATFORM_POSIX_SOCKET
#define NNG_PLATFORM_POSIX_THREAD
#define NNG_PLATFORM_POSIX_PIPEDESC
#define NNG_PLATFORM_POSIX_EPDESC
#define NNG_PLATFORM_POSIX_SOCKADDR
#define NNG_PLATFORM_POSIX_UDP
#define NNG_PLATFORM_POSIX_SIGNALS
#endif


// The following adjustments to the platform may be defined.  These can
// be defined in either platform/config.h or loaded in via external
// defines using cmake.
//
// #define NNG_USE_GETTIMEOFDAY
//	This macro is defined if you lack a working clock_gettime,
//	nanosleep, or pthread_condattr_setclock.  In this case the
//	library uses the system clock for relative sleeps, timers, etc.
//	This can be dangerous if the system clock is changed, so only
//	use this if you have no other choice.  If it appears that
//	the system lacks clock_gettime, then it will choose this automatically.
//	This value may be ignored on platforms that don't use POSIX clocks.
//
// #define NNG_USE_CLOCKID CLOCK_MONOTONIC
//	This macro may be defined to a different clock id (see
//	clock_gettime()).  By default, we use CLOCK_MONOTONIC if it exists,
//	or CLOCK_REALTIME otherwise.  (Except for macOS, which does not have
//	a functional pthread_condattr_setclock().)
//
//	This is ignored if NNG_USE_GETTIMEOFDAY is defined.
//	Platforms that don't use POSIX clocks will probably
//	ignore any setting here.
//
// #define NNG_HAVE_BACKTRACE
//	If your system has a working backtrace(), and backtrace_symbols(),
//	along with <execinfo.h>, you can define this to get richer backtrace
//	information for debugging.
//
// #define NNG_USE_GETRANDOM
// #define NNG_USE_GETENTROPY
// #define NNG_USE_ARC4RANDOM
// #define NNG_USE_DEVURANDOM
//	These are options for obtaining entropy to seed the pRNG.
//	All known modern UNIX variants can support NNG_USE_DEVURANDOM,
//	but the other options are better still, but not portable.

#include <time.h>

#ifdef NNG_PLATFORM_POSIX
#if !defined(NNG_USE_DEVURANDOM) && !defined(NNG_USE_GETENTROPY) && \
    !defined(NNG_USE_GETRANDOM) && !defined(NNG_USE_ARC4RANDOM)
#if defined(NNG_HAVE_GETENTROPY)
#define NNG_USE_GETENTROPY 1
#elif defined(NNG_HAVE_GETRANDOM)
#define NNG_USE_GETRANDOM 1
#elif defined(NNG_HAVE_ARC4RANDOM)
#define NNG_USE_ARC4RANDOM
#else
// It should never hurt to use DEVURANDOM, since if the device does not
// exist then we won't open it.  (Provided: it would be bad if the device
// exists but has somehow very very different semantics.  We don't know
// of any such concerns.)  This won't be used if any of the other options
// are defined and work.
#define NNG_USE_DEVURANDOM 1
#endif
#endif

#ifndef NNG_USE_CLOCKID
#if defined(__APPLE__)
#define NNG_USE_CLOCKID CLOCK_REALTIME
#elif defined(CLOCK_MONOTONIC)
#define NNG_USE_CLOCKID CLOCK_MONOTONIC
#elif defined(CLOCK_REALTIME)
#define NNG_USE_CLOCKID CLOCK_REALTIME
#else
#define NNG_USE_GETTIMEOFDAY
#endif
#endif

#if !defined(NNG_USE_GETTIMEOFDAY) && NNG_USE_CLOCKID != CLOCK_REALTIME
#define NNG_SETCLOCK
#endif

#define NNG_USE_POSIX_RESOLV_GAI 1

// This implementation of notification pipes works ~everywhere on POSIX,
// as it only relies on pipe() and non-blocking I/O.

// So as much as we would like to use eventfd, it turns out to be completely
// busted on some systems (latest Ubuntu release for example).  So we go
// back to the old but repliable pipe() system call.
#undef NNG_USE_EVENTFD

#endif // NNG_PLATFORM_POSIX
