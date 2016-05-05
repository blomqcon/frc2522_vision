#include "camera.h"

using namespace cv;

namespace frc2522cv {
    Mat getDefaultFrame(VideoCapture cap) {
        Mat frame;
        cap >> frame;
        return frame;
    }

    Mat getWebFrame() {
		return Mat();
    }

    Mat getYellowSquareFrame(int i) {
		return Mat();
    }
}
