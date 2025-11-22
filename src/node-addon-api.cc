#include <napi.h>
#include <node_api.h>
#include <thread>

Napi::ThreadSafeFunction g_threadSafeFunction;
std::vector<std::thread> workers;
int32_t id = 0;

struct LogRecord {
  std::int32_t pid;
  std::string message;
  std::uint64_t tid;
};

void callback_from_thread () {
  napi_status acq = g_threadSafeFunction.Acquire();
  if (acq != napi_ok) {
    fprintf(stderr, "uhoh 1\n");
    return;
  };
  auto const record = new LogRecord();
  record->message = "hello";
  record->pid = getpid();
  record->tid = pthread_self();
  napi_status stat = g_threadSafeFunction.BlockingCall(record, [](Napi::Env env, Napi::Function jsCallback, LogRecord* payload) {
    auto obj = Napi::Object::New(env);
    obj["message"] = payload->message;
    obj["pid"] = payload->pid;
    obj["tid"] = payload->tid;
    obj["id"] = id++;
    jsCallback.Call({obj});
    delete payload;
  });
  if (stat != napi_ok) {
    fprintf(stderr, "uhoh 2\n");
    return;
  };
}

void Start(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function cb = info[0].As<Napi::Function>();
  g_threadSafeFunction = Napi::ThreadSafeFunction::New(env, cb, "Foo", 0, 1);
  g_threadSafeFunction.Unref(env);
  for (int i = 0; i < 5; i++) {
    workers.push_back(std::thread([]() {
      for (int i = 0; i < 1000000; i++) {
        callback_from_thread();
        usleep(20);
      }
    }));
  }
}

void Stop(const Napi::CallbackInfo& info) {
  std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
      t.join();
  });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "start"), Napi::Function::New(env, Start));
  exports.Set(Napi::String::New(env, "stop"), Napi::Function::New(env, Stop));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
