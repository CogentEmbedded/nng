//
// Copyright 2022 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// sys_rand32_get exists on Zephyr RTOS only.

#include <random/rand32.h>

#include "core/nng_impl.h"

uint32_t
nni_random(void)
{
	return sys_rand32_get();
}
