#include <opencv2/opencv.hpp>

using namespace cv;

namespace frc2522cv {
    Mat getDefaultFrame(VideoCapture cap);
    Mat getWebFrame();
    Mat getYellowSquareFrame(int i);
}
