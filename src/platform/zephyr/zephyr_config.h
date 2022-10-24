//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include <zephyr/posix/time.h>

#ifdef NNG_PLATFORM_ZEPHYR

#if defined(CLOCK_MONOTONIC)
#define NNG_USE_CLOCKID CLOCK_MONOTONIC
#elif defined(CLOCK_REALTIME)
#define NNG_USE_CLOCKID CLOCK_REALTIME
#else
#error Unsupported Zephyr configuration: need CLOCK_MONOTONIC or CLOCK_REALTIME
#endif

// TODO make it depend on CONFIG_EVENTFD
#define NNG_USE_EVENTFD

#define NNG_THREAD_STACK_SIZE 16348
#define NNG_MAX_THREADS 10
#define NNG_THREAD_PRIORITY 5

#define NNG_RESOLV_CONCURRENCY 1

#endif // NNG_PLATFORM_ZEPHYR
