//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// POSIX pipes.
#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_ZEPHYR

#include <errno.h>

#ifdef NNG_USE_EVENTFD

#include <unistd.h>
#include <zephyr/posix/sys/eventfd.h>

#define NNI_EVENTFD_FLAGS O_NONBLOCK

int
nni_plat_pipe_open(int *wfd, int *rfd)
{
	int fd;

	if ((fd = eventfd(0, NNI_EVENTFD_FLAGS)) < 0) {
		return (nni_plat_errno(errno));
	}
	// (void) fcntl(fd, F_SETFD, FD_CLOEXEC);
	// (void) fcntl(fd, F_SETFL, O_NONBLOCK);

	*wfd = *rfd = fd;
	return (0);
}

void
nni_plat_pipe_raise(int wfd)
{
	eventfd_t one = 1;

	(void) eventfd_write(wfd, one);
}

void
nni_plat_pipe_clear(int rfd)
{
	eventfd_t val;

	(void) eventfd_read(rfd, &val);
}

void
nni_plat_pipe_close(int wfd, int rfd)
{
	NNI_ASSERT(wfd == rfd);
	(void) close(wfd);
}

#else // NNG_USE_EVENTFD

#error Classic pipes are not yet supported on Zephyr

#endif // NNG_USE_EVENTFD

#endif // NNG_PLATFORM_POSIX
