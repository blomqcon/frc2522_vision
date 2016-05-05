
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

namespace frc2522cv {
    namespace filter {
		
		enum ColorSpace {RGB, HSV, YUV};
		
        Mat binary(Mat image, filter::ColorSpace space, Scalar low, Scalar high);
        Mat gray(Mat image, filter::ColorSpace space, Scalar low, Scalar high);
        Mat color(Mat image);
    }
}
