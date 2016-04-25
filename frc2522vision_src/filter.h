
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

namespace frc2522cv {
    namespace filter {
        Mat redBinderBinary(Mat frame);
        Mat redBinderGray(Mat frame);
        Mat redBinderColor(Mat frame);
    }
}
