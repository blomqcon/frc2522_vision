
#include <node.h>

#include "../../frc2522cv/include/detect.h"
#include "../../frc2522cv/include/filter.h"

using namespace v8;
using node::AtExit;

bool validTargetScreenArguments(const FunctionCallbackInfo<Value>& args, Isolate* isolate);
//cv::VideoCapture ipcam = cv::VideoCapture("http://192.168.0.90/mjpg/video.mjpg");
cv::VideoCapture cam;

cv::Mat getCamFrame(cv::VideoCapture cam) {
	cv::Mat frame;
	cam >> frame;
	return frame;
}

Local<Object> createJSPoint(Isolate* isolate, cv::Point2f point) {
	Local<Object> targetPointJS = Object::New(isolate);
	targetPointJS->Set(String::NewFromUtf8(isolate, "x"), Number::New(isolate, point.x));
	targetPointJS->Set(String::NewFromUtf8(isolate, "y"), Number::New(isolate, point.y));
	return targetPointJS;
}

void targetScreenLocation(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  
	if (!validTargetScreenArguments(args, isolate)) {
	 return;
	}
	frc2522cv::Target target = frc2522cv::Target();
	if(!cam.isOpened())
		cam = cv::VideoCapture("http://192.168.0.90/mjpg/video.mjpg");
	cv::Mat image = getCamFrame(cam);
	cv::Mat filteredImage = frc2522cv::filter::binary(image, frc2522cv::filter::HSV, cv::Scalar(0.0, 50.0, 50.0), cv::Scalar(60.0, 255.0, 255.0));
	//cv::Point2f targetPoint = frc2522cv::detect::targetScreenLocation(filteredImage, target, frc2522cv::detect::SimpleBlob);
	cv::Point2f targetPoint(100.0, 500.0);
	cv::Point2f centerPoint(360.0, 240.0);

	Local<Object> obj = Object::New(isolate);
	obj->Set(String::NewFromUtf8(isolate, "targetPoint"), createJSPoint(isolate, targetPoint));
	obj->Set(String::NewFromUtf8(isolate, "centerPoint"), createJSPoint(isolate, centerPoint));
	
	args.GetReturnValue().Set(obj);
}


bool validTargetScreenArguments(const FunctionCallbackInfo<Value>& args, Isolate* isolate) {
	if (args.Length() != 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return false;
	}

	if (!args[0]->IsObject()) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong arguments")));
		return false;
	}

	return true;
}

void cleanupStuff() {
  	cam.~VideoCapture();
}

void cleanup(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	cleanupStuff();
}

static void cleanupAtExit(void* arg) {
  Isolate* isolate = static_cast<Isolate*>(arg);
  HandleScope scope(isolate);
  cleanupStuff();
}

void init(Handle<Object> exports) {
  AtExit(cleanupAtExit, NULL);
  NODE_SET_METHOD(exports, "targetScreenLocation", targetScreenLocation);
  NODE_SET_METHOD(exports, "cleanup", cleanup);
}

NODE_MODULE(addon, init)