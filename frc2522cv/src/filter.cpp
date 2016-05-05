#include "filter.h"

using namespace std;
using namespace cv;
using namespace frc2522cv;

Mat convertColorSpace(Mat image, filter::ColorSpace space) {
	if (space == filter::ColorSpace::HSV) {
		cvtColor(image, image, cv::COLOR_BGR2HSV);
	} else if (space == filter::ColorSpace::YUV) {
		cvtColor(image, image, cv::COLOR_BGR2YUV);
	}
	return image;
}

Mat filter::binary(Mat image, filter::ColorSpace space, Scalar low, Scalar high) {
	Mat blurred(image);
	medianBlur(blurred, blurred, 25);
	//Mat bilat_blurred;
	//bilateralFilter(blurred, bilat_blurred, 9, 100, 3000);
	
	blurred = convertColorSpace(blurred, space);

	Mat blurred_bw;
	inRange(blurred, low, high, blurred_bw);

	return blurred_bw;
}

Mat filter::gray(Mat image, filter::ColorSpace space, Scalar low, Scalar high) {
	Mat blurred(image);
	//Mat bilat_blurred;
	//bilateralFilter(frame, bilat_blurred, 9, 100, 3000);
	medianBlur(blurred, blurred, 25);

	blurred = convertColorSpace(blurred, space);

	Mat blurred_bw;
	inRange(blurred, low, high, blurred_bw);

	Mat blurred_mask;
	blurred.copyTo(blurred_mask, blurred_bw);

	Mat gray, gray_blurred;
	cvtColor(blurred_mask, gray, COLOR_BGR2GRAY);

	medianBlur(gray, gray_blurred, 15);

	dilate(gray_blurred, gray_blurred, Mat(), Point(-1, -1));
	erode(gray_blurred, gray_blurred, Mat());
	return gray_blurred;
}

Mat filter::color(Mat image) {
	return image;
}

