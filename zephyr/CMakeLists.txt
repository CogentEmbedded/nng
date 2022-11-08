#   Copyright 2022 Cogent Embedded Inc.
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"),
#   to deal in the Software without restriction, including without limitation
#   the rights to use, copy, modify, merge, publish, distribute, sublicense,
#   and/or sell copies of the Software, and to permit persons to whom
#   the Software is furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included
#   in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
#   IN THE SOFTWARE.
#

if(CONFIG_NNG)

    set(NNG_DIR ${ZEPHYR_CURRENT_MODULE_DIR})

    zephyr_library()

    zephyr_include_directories(${NNG_DIR}/include)

    find_package(Zephyr REQUIRED)
    set(ZEPHYR_POSIX_INCLUDE_DIR ${ZEPHYR_BASE}/include/zephyr/posix)
    message(STATUS "ZEPHYR_POSIX_INCLUDE_DIR: ${ZEPHYR_POSIX_INCLUDE_DIR}")
    zephyr_library_include_directories(${ZEPHYR_POSIX_INCLUDE_DIR})

    zephyr_library_include_directories(${ZEPHYR_BASE}/include/zephyr)
    zephyr_library_include_directories(${NNG_DIR}/src)

    # char is signed on zephyr
    zephyr_library_compile_options(-Wno-char-subscripts)

    # Platform selection
    zephyr_library_compile_definitions(NNG_PLATFORM_POSIX)
    zephyr_library_compile_definitions(NNG_TRANSPORT_TCP)
    # NNG_TRANSPORT_IPC does not make sense on Zephyr RTOS

    # Custom options
    zephyr_library_compile_definitions(NNG_HAVE_BUS0)
    zephyr_library_compile_definitions(NNG_HAVE_PAIR0)
    zephyr_library_compile_definitions(NNG_HAVE_PAIR1)
    zephyr_library_compile_definitions(NNG_HAVE_PUSH0)
    zephyr_library_compile_definitions(NNG_HAVE_PULL0)
    zephyr_library_compile_definitions(NNG_HAVE_PUB0)
    zephyr_library_compile_definitions(NNG_HAVE_SUB0)
    zephyr_library_compile_definitions(NNG_HAVE_REQ0)
    zephyr_library_compile_definitions(NNG_HAVE_REP0)
    zephyr_library_compile_definitions(NNG_HAVE_SURVEYOR0)
    zephyr_library_compile_definitions(NNG_HAVE_RESPONDENT0)

    zephyr_library_sources(
        ${NNG_DIR}/src/nng.c

        ${NNG_DIR}/src/core/aio.c
        ${NNG_DIR}/src/core/device.c
        ${NNG_DIR}/src/core/dialer.c
        ${NNG_DIR}/src/core/idhash.c
        ${NNG_DIR}/src/core/init.c
        ${NNG_DIR}/src/core/list.c
        ${NNG_DIR}/src/core/listener.c
        ${NNG_DIR}/src/core/lmq.c
        ${NNG_DIR}/src/core/message.c
        ${NNG_DIR}/src/core/msgqueue.c
        ${NNG_DIR}/src/core/options.c
        ${NNG_DIR}/src/core/panic.c
        ${NNG_DIR}/src/core/pipe.c
        ${NNG_DIR}/src/core/pollable.c
        ${NNG_DIR}/src/core/reap.c
        ${NNG_DIR}/src/core/socket.c
        ${NNG_DIR}/src/core/stream.c
        ${NNG_DIR}/src/core/strs.c
        ${NNG_DIR}/src/core/taskq.c
        ${NNG_DIR}/src/core/tcp.c
        ${NNG_DIR}/src/core/thread.c
        ${NNG_DIR}/src/core/timer.c
        ${NNG_DIR}/src/core/url.c

        ${NNG_DIR}/src/supplemental/tls/tls_common.c
        ${NNG_DIR}/src/sp/protocol.c
        ${NNG_DIR}/src/sp/transport.c
        ${NNG_DIR}/src/sp/transport/tcp/tcp.c

        ${NNG_DIR}/src/sp/protocol/bus0/bus.c

        ${NNG_DIR}/src/sp/protocol/pair1/pair1_poly.c
        ${NNG_DIR}/src/sp/protocol/pair0/pair.c
        ${NNG_DIR}/src/sp/protocol/pair1/pair.c

        ${NNG_DIR}/src/sp/protocol/pipeline0/pull.c
        ${NNG_DIR}/src/sp/protocol/pipeline0/push.c

        ${NNG_DIR}/src/sp/protocol/pubsub0/pub.c
        ${NNG_DIR}/src/sp/protocol/pubsub0/sub.c
        ${NNG_DIR}/src/sp/protocol/pubsub0/xsub.c

        ${NNG_DIR}/src/sp/protocol/reqrep0/rep.c
        ${NNG_DIR}/src/sp/protocol/reqrep0/req.c
        ${NNG_DIR}/src/sp/protocol/reqrep0/xrep.c
        ${NNG_DIR}/src/sp/protocol/reqrep0/xreq.c

        ${NNG_DIR}/src/sp/protocol/survey0/respond.c
        ${NNG_DIR}/src/sp/protocol/survey0/survey.c
        ${NNG_DIR}/src/sp/protocol/survey0/xrespond.c
        ${NNG_DIR}/src/sp/protocol/survey0/xsurvey.c

        ${NNG_DIR}/src/platform/posix/posix_tcplisten.c
        ${NNG_DIR}/src/platform/posix/posix_tcpconn.c
        ${NNG_DIR}/src/platform/posix/posix_tcpdial.c
        ${NNG_DIR}/src/platform/posix/posix_pollq_poll.c
        ${NNG_DIR}/src/platform/posix/posix_alloc.c
        ${NNG_DIR}/src/platform/posix/posix_atomic.c
        ${NNG_DIR}/src/platform/posix/posix_clock.c
        ${NNG_DIR}/src/platform/posix/posix_debug.c
        ${NNG_DIR}/src/platform/posix/posix_pipe.c
        ${NNG_DIR}/src/platform/posix/posix_thread.c
        ${NNG_DIR}/src/platform/posix/posix_sockaddr.c
        ${NNG_DIR}/src/platform/posix/posix_resolv_gai.c
        ${NNG_DIR}/src/platform/posix/posix_rand_rand32.c
  	)

    zephyr_library_sources_ifdef(CONFIG_NNG_WEBSOCKETS
        ${NNG_DIR}/src/supplemental/base64/base64.c
        ${NNG_DIR}/src/supplemental/sha1/sha1.c
        ${NNG_DIR}/src/supplemental/http/http_chunk.c
        ${NNG_DIR}/src/supplemental/http/http_client.c
        ${NNG_DIR}/src/supplemental/http/http_conn.c
        ${NNG_DIR}/src/supplemental/http/http_msg.c
        ${NNG_DIR}/src/supplemental/http/http_public.c
        ${NNG_DIR}/src/supplemental/http/http_schemes.c
        ${NNG_DIR}/src/supplemental/http/http_server.c
        ${NNG_DIR}/src/supplemental/websocket/websocket.c
    )
    # Transport selection
    zephyr_library_compile_definitions_ifdef(CONFIG_NNG_WEBSOCKETS NNG_TRANSPORT_WS_WEBSOCKET)

    zephyr_library_sources_ifndef(CONFIG_NNG_WEBSOCKETS
        ${NNG_DIR}/src/supplemental/websocket/stub.c
    )
endif()
