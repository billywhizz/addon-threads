- `Analysis.md` has the basic info on each approach with names for each one tried. When we try a new one, we use this as the tag in the repo

## links

- https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php#c11_Creating_Threads_lambda
- https://www.bogotobogo.com/cplusplus/C11/3_C11_Threading_Lambda_Functions.php
- https://nodejs.github.io/node-addon-examples/special-topics/thread-safe-functions/
- https://github.com/nodejs/node-addon-examples/blob/main/src/6-threadsafe-function/thread_safe_function_with_object_wrap/node-addon-api/tsfn_object_wrap.js
- https://github.com/nodejs/node-addon-examples/blob/main/src/5-async-work/async_work_thread_safe_function/napi/binding.c
- https://github.com/nodejs/node-addon-api/blob/main/napi-inl.h#L6415
- https://github.com/nodejs/node/blob/8dc2bddbd5d0a3a25147c824d81074ace8e4fb1b/src/node_api.cc#L203
- https://github.com/nodejs/node/blob/8dc2bddbd5d0a3a25147c824d81074ace8e4fb1b/src/node_api.cc#L1379
- https://stackoverflow.com/questions/58960713/how-to-use-napi-threadsafe-function-for-nodejs-native-addon
- https://nodejs.org/api/n-api.html#asynchronous-thread-safe-function-calls
- https://docs.libuv.org/en/v1.x/async.html
- https://nikhilm.github.io/uvbook/threads.html
- https://github.com/libuv/libuv/blob/f6e19be74388ff9dfa8583da226d605a7eb4e022/src/unix/async.c#L168

## perf

- https://github.com/jonhoo/inferno

```shell
sudo apt install -y linux-tools-$(uname -r)
cargo install addr2line --features="bin"
sudo sh -c 'echo 1 >/proc/sys/kernel/perf_event_paranoid'
sudo sh -c 'echo 0 >/proc/sys/kernel/kptr_restrict'
perf record --call-graph dwarf node test.js
perf script | inferno-collapse-perf > stacks.folded
cat stacks.folded | inferno-flamegraph > node.svg
google-chrome-stable node.svg
```