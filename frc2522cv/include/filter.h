
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace frc2522cv {
    namespace filter {
		enum ColorSpace {RGB, HSV, YUV};

        cv::Mat binary(cv::Mat image, filter::ColorSpace space, cv::Scalar low, cv::Scalar high);
        cv::Mat gray(cv::Mat image, filter::ColorSpace space, cv::Scalar low, cv::Scalar high);
        cv::Mat color(cv::Mat image);
    }
}
