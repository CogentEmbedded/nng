//
// Copyright 2022 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2017 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_ZEPHYR

#include <errno.h>
#include <string.h>
#include <zephyr/posix/time.h>

nni_time
nni_clock(void)
{
	struct timespec ts;
	nni_time        msec;

	if (clock_gettime(NNG_USE_CLOCKID, &ts) != 0) {
		// This should never ever occur.
		nni_panic("clock_gettime failed: %s", strerror(errno));
	}

	msec = ts.tv_sec;
	msec *= 1000;
	msec += (ts.tv_nsec / 1000000);
	return (msec);
}

void
nni_msleep(nni_duration ms)
{
	struct timespec ts;

	ts.tv_sec  = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;

	// Do this in a loop, so that interrupts don't actually wake us.
	while (ts.tv_sec || ts.tv_nsec) {
		if (nanosleep(&ts, &ts) == 0) {
			break;
		}
	}
}

#endif // NNG_PLATFORM_ZEPHYR
