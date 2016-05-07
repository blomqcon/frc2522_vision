#include <opencv2/opencv.hpp>

namespace frc2522cv {
	namespace camera {
		cv::Mat getDefaultFrame(cv::VideoCapture cap);
		cv::Mat getWebFrame();
		cv::Mat getVideoFrame(std::string video, int i);
	}
    
}
