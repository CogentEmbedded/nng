//
// Copyright 2020 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
// Copyright 2019 Devolutions <info@devolutions.net>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include "core/nng_impl.h"

/*
 TODO implement using Zephyr IPC,
 see https://docs.zephyrproject.org/apidoc/latest/group__ipc__service__api.html
 also see https://docs.zephyrproject.org/apidoc/latest/group__ipc.html
 also see
 https://docs.zephyrproject.org/latest/samples/subsys/ipc/ipc_service/README.html
 */

int
ipc_listener_listen(void *arg)
{
	// FIXME
	NNI_ARG_UNUSED(arg);
	return (NNG_ENOTSUP);
}

int
nni_ipc_listener_alloc(nng_stream_listener **lp, const nng_url *url)
{
	// FIXME
	NNI_ARG_UNUSED(lp);
	NNI_ARG_UNUSED(url);

	return (NNG_ENOTSUP);
}
