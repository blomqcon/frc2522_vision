#include <opencv2/opencv.hpp>

namespace frc2522cv {
	namespace camera {
    	//static cv::VideoCapture webcam = cv::VideoCapture(0);
 		//static cv::VideoCapture ipcam;// = cv::VideoCapture("http://192.168.0.90/mjpg/video.mjpg");
		//static cv::VideoCapture testVid;// = cv::VideoCapture("../../../../_test_clips/medium_room.avi");

 		cv::Mat getDefaultFrame();
 		cv::Mat getWebFrame();
 		cv::Mat getVideoFrame(std::string video, int i);
	}

}
