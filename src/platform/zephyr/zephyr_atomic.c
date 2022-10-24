//
// Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2018 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

// POSIX atomics.

#include "core/nng_impl.h"

#ifdef NNG_PLATFORM_ZEPHYR

bool
nni_atomic_flag_test_and_set(nni_atomic_flag *f)
{
	return atomic_set(&f->f, (atomic_t)true);
}

void
nni_atomic_flag_reset(nni_atomic_flag *f)
{
	atomic_set(&f->f, (atomic_t)false);
}

void
nni_atomic_set_bool(nni_atomic_bool *v, bool b)
{
	atomic_set(&v->b, (atomic_t)!!b);
}

bool
nni_atomic_get_bool(nni_atomic_bool *v)
{
	return !!atomic_get(&v->b);
}

bool
nni_atomic_swap_bool(nni_atomic_bool *v, bool b)
{
	return atomic_set(&v->b, (atomic_t)!!b);
}

void
nni_atomic_init_bool(nni_atomic_bool *v)
{
	v->b = ATOMIC_INIT((atomic_t)false);
}

void
nni_atomic_init(nni_atomic_int *v)
{
	v->v = ATOMIC_INIT(0);
}

void
nni_atomic_add(nni_atomic_int *v, int bump)
{
	atomic_add(&v->v, bump);
}

void
nni_atomic_sub(nni_atomic_int *v, int bump)
{
	atomic_sub(&v->v, bump);
}

int
nni_atomic_get(nni_atomic_int *v)
{
	return atomic_get(&v->v);
}

void
nni_atomic_set(nni_atomic_int *v, int i)
{
	atomic_set(&v->v, i);
}

void *
nni_atomic_get_ptr(nni_atomic_ptr *v)
{
	return (void *)atomic_ptr_get(&v->v);
}

void
nni_atomic_set_ptr(nni_atomic_ptr *v, void *p)
{
	atomic_ptr_set(&v->v, (atomic_ptr_t)p);
}

int
nni_atomic_swap(nni_atomic_int *v, int i)
{
	return atomic_set(&v->v, i);
}

void
nni_atomic_inc(nni_atomic_int *v)
{
	atomic_inc(&v->v);
}

void
nni_atomic_dec(nni_atomic_int *v)
{
	atomic_dec(&v->v);
}

int
nni_atomic_dec_nv(nni_atomic_int *v)
{
	return atomic_dec(&v->v);
}

bool
nni_atomic_cas(nni_atomic_int *v, int comp, int new)
{
	return atomic_cas(&v->v, comp, new);
}

void
nni_atomic_add64(nni_atomic_u64 *v, uint64_t bump)
{
	atomic_add(&v->v, (atomic_t)bump);
}

void
nni_atomic_sub64(nni_atomic_u64 *v, uint64_t bump)
{
	atomic_sub(&v->v, (atomic_t)bump);
}

uint64_t
nni_atomic_get64(nni_atomic_u64 *v)
{
	return (uint64_t)atomic_get(&v->v);
}

void
nni_atomic_set64(nni_atomic_u64 *v, uint64_t u)
{
	atomic_set(&v->v, (atomic_t)u);
}

uint64_t
nni_atomic_swap64(nni_atomic_u64 *v, uint64_t u)
{
	return (uint64_t)atomic_set(&v->v, (atomic_t) u);
}

void
nni_atomic_init64(nni_atomic_u64 *v)
{
	v->v = ATOMIC_INIT((atomic_t)v);
}

void
nni_atomic_inc64(nni_atomic_u64 *v)
{
	atomic_inc(&v->v);
}

uint64_t
nni_atomic_dec64_nv(nni_atomic_u64 *v)
{
	return (uint64_t)atomic_dec(&v->v);
}

bool
nni_atomic_cas64(nni_atomic_u64 *v, uint64_t comp, uint64_t new)
{
	return atomic_cas(&v->v, (atomic_t) comp, (atomic_t) new);
}

#endif // NNG_PLATFORM_POSIX
