
#include <node.h>

#include "..\..\frc2522cv\include\detect.h"
#include "..\..\frc2522cv\include\filter.h"
#include "..\..\frc2522cv\include\camera.h"

using namespace v8;

Handle<Value> targetScreenLocation(const v8::Arguments &args) {
  HandleScope scope;

  if (!validTargetScreenArguments(args)) {
	  return scope.Close(Undefined());
  }

  frc2522cv::Target target = new frc2522cv::Target();
  cv::Mat image = frc2522cv::camera::getWebFrame();
  cv::Mat filteredImage = frc2522cv::filter::binary(image, frc2522cv::filter::ColorSpace.HSV, cv::Scalar(0.0, 50.0, 50.0), cv::Scalar(60.0, 255.0, 255.0));
  //cv::Point2f targetLocation = frc2522cv::targetScreenLocation(target, frc2522cv::detect::Type.SimpleBlob, filteredImage);
  cv::Point2f targetLocation(1.0, 5.0);

  Local<Object> obj = Object::New();
  
  Local<Object> point = Object::New();
  //point->Set(v8::String::, "x", NewStringType::kNormal), Number::New(targetLocation.x));
  //point->Set(v8::String::NewSymbol("y"), Number::New(targetLocation.y));
  
  //obj->Set(v8::String::NewSymbol("point"), point);

  return scope.Close(obj);
}

bool validTargetScreenArguments(const Arguments& args) {
	if (args.Length() != 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return false;
	}

	if (!args[0]->IsObject()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument")));
		return false;
	}

	return true;
}


void Init(Handle<Object> exports, Handle<Object> module) {
	exports->Set(String::NewSymbol("targetScreenLocation"), FunctionTemplate::New(targetScreenLocation)->GetFunction());
}

NODE_MODULE(addon, Init)
