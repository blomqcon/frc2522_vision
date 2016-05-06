#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace frc2522cv {
	namespace camera {
		Mat getDefaultFrame(VideoCapture cap);
		Mat getWebFrame();
		Mat getVideoFrame(string video, int i);
	}
    
}
