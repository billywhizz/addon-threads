#include <napi.h>
#include <node_api.h>
#include <thread>
#include <iostream>

struct workerThread {
  std::thread thread;
  bool running = true;
  ~workerThread () {
    if (thread.joinable()) {
      std::cerr << "join : " << thread.get_id() << "\n";
      thread.join();
    }
  }
};

Napi::ThreadSafeFunction g_threadSafeFunction;
std::vector<workerThread*> workers;
int32_t id = 1;

struct LogRecord {
  std::int32_t pid;
  std::string message;
  std::uint64_t tid;
};

bool callback_from_thread (auto const record) {
  auto const status = g_threadSafeFunction.NonBlockingCall(record, [](Napi::Env env, Napi::Function jsCallback, LogRecord* record) {
    auto obj = Napi::Object::New(env);
    obj["message"] = record->message;
    obj["pid"] = record->pid;
    obj["tid"] = record->tid;
    obj["id"] = id++;
    jsCallback.Call({obj});
//    delete record;
  });
  if (status == napi_closing) {
    fprintf(stderr, "closing\n");
    return false;
  }
  if (status != napi_ok) {
    fprintf(stderr, "uhoh 2\n");
    return false;
  };
  return true;
}

void Start(const Napi::CallbackInfo& info) {
  auto const env = info.Env();
  auto const cb = info[0].As<Napi::Function>();
  g_threadSafeFunction = Napi::ThreadSafeFunction::New(env, cb, "Foo", 0, 1);
//  g_threadSafeFunction.Unref(env);
  for (int i = 0; i < 8; i++) {
    auto const worker = new workerThread();
    worker->thread = std::thread([worker]() {
      auto const record = new LogRecord();
      record->message = "hello";
      record->pid = getpid();
      record->tid = pthread_self();
      while(1) {
        callback_from_thread(record);
        if (!worker->running) break;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
      }
      fprintf(stderr, "closing thread: %b\n", worker->running);
      delete record;
    });
    workers.push_back(worker);
  }
}

void Stop(const Napi::CallbackInfo& info) {
  std::for_each(workers.begin(), workers.end(), [](struct workerThread* worker) {
    worker->running = false;
  });
  std::for_each(workers.begin(), workers.end(), [](struct workerThread* worker) {
    delete worker;
  });
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
