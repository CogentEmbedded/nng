# SPDX-License-Identifier: MIT

if(CONFIG_NNG)

	set(NNG_DIR ${ZEPHYR_CURRENT_MODULE_DIR})

 	zephyr_library()

  	zephyr_include_directories(${NNG_DIR}/include)
  	zephyr_include_directories(${NNG_DIR}/src)

	# char is signed on zephyr
	zephyr_compile_options(-Wno-char-subscripts)

	# Platform selection
	zephyr_compile_definitions(NNG_PLATFORM_ZEPHYR)
	zephyr_compile_definitions(NNG_TRANSPORT_TCP)

	# Custom options
	zephyr_compile_definitions(NNG_HAVE_BUS0)
	zephyr_compile_definitions(NNG_HAVE_PAIR0)
	zephyr_compile_definitions(NNG_HAVE_PAIR1)
	zephyr_compile_definitions(NNG_HAVE_PUSH0)
	zephyr_compile_definitions(NNG_HAVE_PULL0)
	zephyr_compile_definitions(NNG_HAVE_PUB0)
	zephyr_compile_definitions(NNG_HAVE_SUB0)
	zephyr_compile_definitions(NNG_HAVE_REQ0)
	zephyr_compile_definitions(NNG_HAVE_REP0)
	zephyr_compile_definitions(NNG_HAVE_SURVEYOR0)
	zephyr_compile_definitions(NNG_HAVE_RESPONDENT0)

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

		${NNG_DIR}/src/sp/transport/ipc/ipc.c
		${NNG_DIR}/src/sp/transport/tcp/tcp.c
		${NNG_DIR}/src/supplemental/websocket/stub.c

		${NNG_DIR}/src/platform/zephyr/zephyr_alloc.c
		${NNG_DIR}/src/platform/zephyr/zephyr_atomic.c
		${NNG_DIR}/src/platform/zephyr/zephyr_clock.c
		${NNG_DIR}/src/platform/zephyr/zephyr_debug.c
		${NNG_DIR}/src/platform/zephyr/zephyr_ipcdial.c
		${NNG_DIR}/src/platform/zephyr/zephyr_ipclisten.c
		${NNG_DIR}/src/platform/zephyr/zephyr_pipe.c
		${NNG_DIR}/src/platform/zephyr/zephyr_pollq_poll.c
		${NNG_DIR}/src/platform/zephyr/zephyr_rand.c
		${NNG_DIR}/src/platform/zephyr/zephyr_resolv.c
		${NNG_DIR}/src/platform/zephyr/zephyr_tcpconn.c
		${NNG_DIR}/src/platform/zephyr/zephyr_tcpdial.c
		${NNG_DIR}/src/platform/zephyr/zephyr_tcplisten.c
		${NNG_DIR}/src/platform/zephyr/zephyr_thread.c
		${NNG_DIR}/src/platform/zephyr/zephyr_sockaddr.c
  	)
endif()
