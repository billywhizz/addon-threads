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

## assay_0002

```shell
(lldb) target create "/home/andrew/.node/24/bin/node" --core "core.270626"
Core file '/media/andrew/OCZ/source2023/just-js/addon-threads/core.270626' (x86_64) was loaded.
(lldb) bt
* thread #1, name = 'MainThread', stop reason = SIGABRT: sent by tkill system call (sender pid=270626, uid=1000)
  * frame #0: 0x000073c5024969fc libc.so.6`__pthread_kill_implementation(no_tid=0, signo=6, threadid=127289990617216) at pthread_kill.c:44:76
    frame #1: 0x000073c5024969b0 libc.so.6`__pthread_kill_internal(signo=6, threadid=127289990617216) at pthread_kill.c:78:10 [inlined]
    frame #2: 0x000073c5024969b0 libc.so.6`__GI___pthread_kill(threadid=127289990617216, signo=6) at pthread_kill.c:89:10
    frame #3: 0x000073c502442476 libc.so.6`__GI_raise(sig=6) at raise.c:26:13
    frame #4: 0x000073c5024287f3 libc.so.6`__GI_abort at abort.c:79:7
    frame #5: 0x0000000000f410c7 node`node::OnFatalError(char const*, char const*) + 262
    frame #6: 0x00000000010624f5 node`napi_fatal_error + 149
    frame #7: 0x000073c5026d55da node-addon-api.node`Napi::Error::Fatal(location="Error::ThrowAsJavaScriptException", message="napi_throw") at napi-inl.h:3173:19
    frame #8: 0x000073c5026d5c2d node-addon-api.node`Napi::Error::ThrowAsJavaScriptException(this=0x00007fff26ac3d80) const at napi-inl.h:3367:5
    frame #9: 0x000073c5026d8e44 node-addon-api.node`bool Napi::Object::Set<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>(this=0x00007fff26ac3e20, utf8name="message", value="hello") const at napi-inl.h:1733:3
    frame #10: 0x000073c5026d7cc4 node-addon-api.node`bool Napi::Object::Set<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>(this=0x00007fff26ac3e20, utf8name="message", value="hello") const at napi-inl.h:1739:13
    frame #11: 0x000073c5026d8090 node-addon-api.node`Napi::Object::PropertyLValue<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>& Napi::Object::PropertyLValue<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>::operator=<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>(this=0x00007fff26ac3ec0, value="hello") at napi-inl.h:1573:32
    frame #12: 0x000073c5026d3277 node-addon-api.node`operator(__closure=0x000073c49c001aa8, env=Env @ 0x00007fff26ac3e70, jsCallback=Function @ 0x00007fff26ac3e60, payload=0x000073c49c0012f0) at node-addon-api.cc:34:31
    frame #13: 0x000073c5026d3a2f node-addon-api.node`operator(__closure=0x000073c49c001aa0, env=Env @ 0x00007fff26ac3f30, jsCallback=Function @ 0x00007fff26ac3f20) at napi-inl.h:6345:13
    frame #14: 0x000073c5026d403a node-addon-api.node`std::__invoke_impl<void, Napi::ThreadSafeFunction::BlockingCall<LogRecord, callback_from_thread()::<lambda(Napi::Env, Napi::Function, LogRecord*)> >(LogRecord*, callback_from_thread()::<lambda(Napi::Env, Napi::Function, LogRecord*)>) const::<lambda(Napi::Env, Napi::Function)>&, Napi::Env, Napi::Function>((null)=__invoke_other @ 0x00007fff26ac3f90, __f=0x000073c49c001aa0, (null)=0x00007fff26ac4020, (null)=0x00007fff26ac4010) &) at invoke.h:61:36
    frame #15: 0x000073c5026d3eb9 node-addon-api.node`std::__invoke_r<void, Napi::ThreadSafeFunction::BlockingCall<LogRecord, callback_from_thread()::<lambda(Napi::Env, Napi::Function, LogRecord*)> >(LogRecord*, callback_from_thread()::<lambda(Napi::Env, Napi::Function, LogRecord*)>) const::<lambda(Napi::Env, Napi::Function)>&, Napi::Env, Napi::Function>(__fn=0x000073c49c001aa0, (null)=0x00007fff26ac4020, (null)=0x00007fff26ac4010) &) at invoke.h:111:28
    frame #16: 0x000073c5026d3d51 node-addon-api.node`std::_Function_handler<void(Napi::Env, Napi::Function), Napi::ThreadSafeFunction::BlockingCall<LogRecord, callback_from_thread()::<lambda(Napi::Env, Napi::Function, LogRecord*)> >(LogRecord*, callback_from_thread()::<lambda(Napi::Env, Napi::Function, LogRecord*)>) const::<lambda(Napi::Env, Napi::Function)> >::_M_invoke(__functor=0x000073c49c001aa0, __args#0=0x00007fff26ac4020, __args#1=0x00007fff26ac4010) at std_function.h:290:30
    frame #17: 0x000073c5026d7edd node-addon-api.node`std::function<void (Napi::Env, Napi::Function)>::operator()(this=0x000073c49c001aa0, __args#0=Env @ 0x00007fff26ac4020, __args#1=Function @ 0x00007fff26ac4010) const at std_function.h:590:9
    frame #18: 0x000073c5026d6dc2 node-addon-api.node`Napi::ThreadSafeFunction::CallJS(napi_env__*, napi_value__*, void*, void*)::'lambda'()::operator()(__closure=0x00007fff26ac40e0) const at napi-inl.h:6477:25
    frame #19: 0x000073c5026d7f00 node-addon-api.node`void Napi::details::WrapVoidCallback<Napi::ThreadSafeFunction::CallJS(napi_env__*, napi_value__*, void*, void*)::'lambda'()>((null)=0x000000001efc5bb0, callback=(unnamed struct) @ 0x00007fff26ac40e0) at napi-inl.h:156:11
    frame #20: 0x000073c5026d6eb5 node-addon-api.node`Napi::ThreadSafeFunction::CallJS(env=0x000000001efc5bb0, jsCallback=0x000000001ef73d28, (null)=0x0000000000000000, data=0x000073c49c001aa0) at napi-inl.h:6474:28
    frame #21: 0x0000000001061ab3 node`v8impl::(anonymous namespace)::ThreadSafeFunction::AsyncCb(uv_async_s*) + 419
    frame #22: 0x000000000210d4c3 node`uv__async_io(loop=0x0000000006e5ea60, w=<unavailable>, events=<unavailable>) at async.c:208:5
    frame #23: 0x0000000002123f6a node`uv__io_poll(loop=0x0000000006e5ea60, timeout=<unavailable>) at linux.c:1565:11
    frame #24: 0x000000000210e187 node`uv_run(loop=0x0000000006e5ea60, mode=UV_RUN_ONCE) at core.c:460:5
    frame #25: 0x00000000010095f8 node`node::Environment::CleanupHandles() + 216
    frame #26: 0x0000000001009684 node`node::Environment::RunCleanup() + 100
    frame #27: 0x0000000000f9251b node`node::FreeEnvironment(node::Environment*) + 123
    frame #28: 0x00000000011195f6 node`node::NodeMainInstance::Run() + 150
    frame #29: 0x0000000001058782 node`node::Start(int, char**) + 1202
    frame #30: 0x000073c502429d90 libc.so.6`__libc_start_call_main(main=(node`main), argc=2, argv=0x00007fff26ac8a18) at libc_start_call_main.h:58:16
    frame #31: 0x000073c502429e40 libc.so.6`__libc_start_main_impl(main=(node`main), argc=2, argv=0x00007fff26ac8a18, init=<unavailable>, fini=<unavailable>, rtld_fini=<unavailable>, stack_end=0x00007fff26ac8a08) at libc-start.c:392:3
    frame #32: 0x0000000000f8761e node`_start + 46
```


```shell
(lldb) target create "/home/andrew/.node/24/bin/node" --core "core.283659"
Core file '/media/andrew/OCZ/source2023/just-js/addon-threads/core.283659' (x86_64) was loaded.
(lldb) bt
* thread #1, name = 'MainThread', stop reason = SIGSEGV: sent by tkill system call (sender pid=283659, uid=1000)
  * frame #0: 0x00007a2f162a53fe libc.so.6`__GI___libc_free(mem=0x0570000000000000) at malloc.c:3368:7
    frame #1: 0x00007a2f16291774 libc.so.6`__GI___nptl_free_tcb(pd=0x000000002a4f0462) at nptl_free_tcb.c:35:11
    frame #2: 0x00007a2f16291758 libc.so.6`__GI___nptl_free_tcb(pd=0x000000002a4f0462) at nptl_free_tcb.c:24:1
    frame #3: 0x00007a2f1629659c libc.so.6`__pthread_clockjoin_ex(threadid=709821538, thread_return=0x0000000000000000, clockid=0, abstime=0x0000000000000000, block=<unavailable>) at pthread_join_common.c:128:7
    frame #4: 0x00007a2f166dc2c7 libstdc++.so.6`std::thread::join() + 23
    frame #5: 0x00007a2f168487a3 node-addon-api.node`operator(__closure=0x00007ffecf9957bf, worker=0x000000002a4f23c0) at node-addon-api.cc:70:24
    frame #6: 0x00007a2f168487f9 node-addon-api.node`std::for_each<__gnu_cxx::__normal_iterator<workerThread**, std::vector<workerThread*> >, Stop(const Napi::CallbackInfo&)::<lambda(workerThread*)> >(__first=__normal_iterator<workerThread**, std::vector<workerThread*, std::allocator<workerThread*> > > @ 0x00007ffecf9957c8, __last=__normal_iterator<workerThread**, std::vector<workerThread*, std::allocator<workerThread*> > > @ 0x00007ffecf9957c0, __f=(unnamed struct) @ 0x00007ffecf9957bf)) at stl_algo.h:3820:5
    frame #7: 0x00007a2f168488a0 node-addon-api.node`Stop(info=0x00007ffecf995850) at node-addon-api.cc:69:16
    frame #8: 0x00007a2f1684e58a node-addon-api.node`Napi::details::CallbackData<void (*)(Napi::CallbackInfo const&), void>::Wrapper(napi_env__*, napi_callback_info__*)::'lambda'()::operator()(__closure=0x00007ffecf9958f0) const at napi-inl.h:184:21
    frame #9: 0x00007a2f1684f27a node-addon-api.node`napi_value__* Napi::details::WrapCallback<Napi::details::CallbackData<void (*)(Napi::CallbackInfo const&), void>::Wrapper(napi_env__*, napi_callback_info__*)::'lambda'()>((null)=0x000000002a5430c0, callback=(unnamed struct) @ 0x00007ffecf9958f0) at napi-inl.h:107:18
    frame #10: 0x00007a2f1684e618 node-addon-api.node`Napi::details::CallbackData<void (*)(Napi::CallbackInfo const&), void>::Wrapper(env=0x000000002a5430c0, info=0x00007ffecf995940) at napi-inl.h:179:33
    frame #11: 0x0000000001030181 node`v8impl::(anonymous namespace)::FunctionCallbackWrapper::Invoke(v8::FunctionCallbackInfo<v8::Value> const&) + 97
    frame #12: 0x00007a2ef758f08d
    frame #13: 0x00007a2ef758d654
    frame #14: 0x00007a2ef758d654
    frame #15: 0x00007a2ef758d654
    frame #16: 0x00007a2ef758b21c
    frame #17: 0x00007a2ef758af67
    frame #18: 0x0000000001531b61 node`v8::internal::(anonymous namespace)::Invoke(v8::internal::Isolate*, v8::internal::(anonymous namespace)::InvokeParams const&) + 353
    frame #19: 0x0000000001532a0f node`v8::internal::Execution::Call(v8::internal::Isolate*, v8::internal::DirectHandle<v8::internal::Object>, v8::internal::DirectHandle<v8::internal::Object>, v8::base::Vector<v8::internal::DirectHandle<v8::internal::Object> const>) + 95
    frame #20: 0x000000000139f807 node`v8::Function::Call(v8::Isolate*, v8::Local<v8::Context>, v8::Local<v8::Value>, int, v8::Local<v8::Value>*) + 375
    frame #21: 0x000000000101a0b2 node`node::Environment::RunTimers(uv_timer_s*) + 434
    frame #22: 0x000000000210a534 node`uv__run_timers(loop=<unavailable>) at timer.c:193:5
    frame #23: 0x000000000210e35a node`uv_run(loop=0x0000000006e5ea60, mode=UV_RUN_DEFAULT) at core.c:478:5
    frame #24: 0x0000000000f8c055 node`node::SpinEventLoopInternal(node::Environment*) + 357
    frame #25: 0x0000000001119642 node`node::NodeMainInstance::Run() + 226
    frame #26: 0x0000000001058782 node`node::Start(int, char**) + 1202
    frame #27: 0x00007a2f16229d90 libc.so.6`__libc_start_call_main(main=(node`main), argc=2, argv=0x00007ffecf996428) at libc_start_call_main.h:58:16
    frame #28: 0x00007a2f16229e40 libc.so.6`__libc_start_main_impl(main=(node`main), argc=2, argv=0x00007ffecf996428, init=<unavailable>, fini=<unavailable>, rtld_fini=<unavailable>, stack_end=0x00007ffecf996418) at libc-start.c:392:3
    frame #29: 0x0000000000f8761e node`_start + 46
(lldb) quit
```