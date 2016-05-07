#include "../include/camera.h"

using namespace cv;

namespace frc2522cv {
    Mat camera::getDefaultFrame(VideoCapture cap) {
        Mat frame;
        cap >> frame;
        return frame;
    }

    Mat camera::getWebFrame() {
		return Mat();
    }

    Mat camera::getVideoFrame(std::string video, int i) {
		return Mat();
    }
}
