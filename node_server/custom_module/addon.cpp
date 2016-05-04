#include <node.h>
#include "../../frc2522vision_src/detect.h"

using namespace v8;

Handle<Value> Add(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  double arg0 = args[0]->NumberValue();
  double arg1 = args[1]->NumberValue();

  Local<Number> num = Number::New(frc2522cv::detect::getTargetLocation(arg0, arg1));


  return scope.Close(num);
}

Handle<Value> getBinderLocation(const Arguments& args) {
  HandleScope scope;

  Local<Object> obj = Object::New();
  Local<Object> pointJS = Object::New();
  //cv::Point2f point = frc2522cv::detect::redBinderBlob(frame);
  cv::Point2f point(1.0, 5.0);
  pointJS->Set(String::NewSymbol("x"), Number::New(point.x));
  pointJS->Set(String::NewSymbol("y"), Number::New(point.y));

  //Handle<String> hello = String::New("hello from c++ world!");
  obj->Set(String::NewSymbol("point"), pointJS);

  return scope.Close(obj);
}


void Init(Handle<Object> exports, Handle<Object> module) {
  exports->Set(String::NewSymbol("add"), FunctionTemplate::New(Add)->GetFunction());
  exports->Set(String::NewSymbol("getBinderLocation"), FunctionTemplate::New(getBinderLocation)->GetFunction());
}

NODE_MODULE(addon, Init)
