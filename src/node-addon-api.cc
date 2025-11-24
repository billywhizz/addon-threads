#include <chrono>
#include <napi.h>
#include <node_api.h>
#include <thread>

struct workerThread {
  std::thread thread;
  bool running = true;

  ~workerThread () {
    if (thread.joinable()) {
      thread.join();
    }
  }
};

Napi::ThreadSafeFunction g_threadSafeFunction;
std::vector<std::unique_ptr<workerThread>> workers;
std::int32_t id = 0;

struct LogRecord {
  std::int32_t pid;
  std::string message;
  std::uint64_t tid;
};

void callback_from_thread () {
/*
  napi_status acq = g_threadSafeFunction.Acquire();
  if (acq != napi_ok) {
    fprintf(stderr, "uhoh 1\n");
    return;
  };
*/
  auto const record = new LogRecord();
  record->message = "hello";
  record->pid = getpid();
  record->tid = pthread_self();
  auto const status = g_threadSafeFunction.BlockingCall(record, [](Napi::Env env, Napi::Function jsCallback, LogRecord* record) {
    auto obj = Napi::Object::New(env);
    obj["message"] = record->message;
    obj["pid"] = record->pid;
    obj["tid"] = record->tid;
    obj["id"] = id++;
    jsCallback.Call({obj});
    delete record;
  });
  if (status == napi_closing) {
    return;
  }
  if (status != napi_ok) {
    fprintf(stderr, "uhoh 2\n");
    return;
  };
}

void Start(const Napi::CallbackInfo& info) {
  auto const env = info.Env();
  auto const cb = info[0].As<Napi::Function>();
  g_threadSafeFunction = Napi::ThreadSafeFunction::New(env, cb, "Foo", 0, 1);
  g_threadSafeFunction.Unref(env);
  for (int i = 0; i < 1; i++) {
    auto worker = std::make_unique<workerThread>();
    worker->thread = std::thread([w = worker.get()]() {
      while(w->running) {
        callback_from_thread();
        std::this_thread::sleep_for(std::chrono::microseconds(20));
      }
    });
    workers.push_back(std::move(worker));
  }
}

void Stop(const Napi::CallbackInfo& info) {
  for (auto it = workers.begin(); it != workers.end(); ++it) {
    (*it)->running = false;
  }
  workers.clear();
  g_threadSafeFunction.Abort();
  g_threadSafeFunction = Napi::ThreadSafeFunction();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "start"), Napi::Function::New(env, Start));
  exports.Set(Napi::String::New(env, "stop"), Napi::Function::New(env, Stop));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
