## assay_0001

This implementation works for some time and eventually seems to deadlock, with no more output on the terminal.
After some time it then crashes. This is the backtrace from the core dump.

```shell
(lldb) target create "/home/andrew/.node/24/bin/node" --core "core.257846"
Core file '/media/andrew/OCZ/source2023/just-js/addon-threads/core.257846' (x86_64) was loaded.
(lldb) bt
* thread #1, name = 'MainThread', stop reason = SIGABRT: sent by tkill system call (sender pid=257846, uid=1000)
  * frame #0: 0x000074d0646969fc libc.so.6`__pthread_kill_implementation(no_tid=0, signo=6, threadid=128438392785024) at pthread_kill.c:44:76
    frame #1: 0x000074d0646969b0 libc.so.6`__pthread_kill_internal(signo=6, threadid=128438392785024) at pthread_kill.c:78:10 [inlined]
    frame #2: 0x000074d0646969b0 libc.so.6`__GI___pthread_kill(threadid=128438392785024, signo=6) at pthread_kill.c:89:10
    frame #3: 0x000074d064642476 libc.so.6`__GI_raise(sig=6) at raise.c:26:13
    frame #4: 0x000074d0646287f3 libc.so.6`__GI_abort at abort.c:79:7
    frame #5: 0x0000000000f410c7 node`node::OnFatalError(char const*, char const*) + 262
    frame #6: 0x00000000010624f5 node`napi_fatal_error + 149
    frame #7: 0x000074d064c38d5e node-addon-api.node`Napi::Error::Fatal(char const*, char const*) + 30
    frame #8: 0x000074d064c397fd node-addon-api.node`Napi::Error::ThrowAsJavaScriptException() const + 2509
    frame #9: 0x000074d064c352cb node-addon-api.node`callback_from_thread()::'lambda'(Napi::Env, Napi::Function, LogRecord*)::operator()(Napi::Env, Napi::Function, LogRecord*) const (.constprop.0) + 4731
    frame #10: 0x000074d064c3a45e node-addon-api.node`Napi::ThreadSafeFunction::CallJS(napi_env__*, napi_value__*, void*, void*) + 126
    frame #11: 0x0000000001061ab3 node`v8impl::(anonymous namespace)::ThreadSafeFunction::AsyncCb(uv_async_s*) + 419
    frame #12: 0x000000000210d4c3 node`uv__async_io(loop=0x0000000006e5ea60, w=<unavailable>, events=<unavailable>) at async.c:208:5
    frame #13: 0x0000000002123f6a node`uv__io_poll(loop=0x0000000006e5ea60, timeout=<unavailable>) at linux.c:1565:11
    frame #14: 0x000000000210e187 node`uv_run(loop=0x0000000006e5ea60, mode=UV_RUN_ONCE) at core.c:460:5
    frame #15: 0x00000000010095f8 node`node::Environment::CleanupHandles() + 216
    frame #16: 0x0000000001009684 node`node::Environment::RunCleanup() + 100
    frame #17: 0x0000000000f9251b node`node::FreeEnvironment(node::Environment*) + 123
    frame #18: 0x00000000011195f6 node`node::NodeMainInstance::Run() + 150
    frame #19: 0x0000000001058782 node`node::Start(int, char**) + 1202
    frame #20: 0x000074d064629d90 libc.so.6`__libc_start_call_main(main=(node`main), argc=2, argv=0x00007ffc0c0f3b78) at libc_start_call_main.h:58:16
    frame #21: 0x000074d064629e40 libc.so.6`__libc_start_main_impl(main=(node`main), argc=2, argv=0x00007ffc0c0f3b78, init=<unavailable>, fini=<unavailable>, rtld_fini=<unavailable>, stack_end=0x00007ffc0c0f3b68) at libc-start.c:392:3
    frame #22: 0x0000000000f8761e node`_start + 46
```
