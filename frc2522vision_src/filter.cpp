#include "filter.h"

using namespace std;
using namespace cv;
using namespace frc2522cv;


Mat filter::redBinderBinary(Mat frame) {
    Mat blurred(frame);
    //Mat bilat_blurred;
    //bilateralFilter(frame, bilat_blurred, 9, 100, 3000);
    medianBlur(blurred, blurred, 25);

    cvtColor(blurred, blurred, cv::COLOR_BGR2HSV);
    //cvtColor(blurred, blurred, cv::COLOR_BGR2YUV);

    Mat blurred_bw;
    inRange(blurred, Scalar(160, 80, 80), Scalar(190, 255, 255), blurred_bw);

    return blurred_bw;
}

Mat filter::redBinderGray(Mat frame) {
    Mat blurred(frame);
    //Mat bilat_blurred;
    //bilateralFilter(frame, bilat_blurred, 9, 100, 3000);
    medianBlur(blurred, blurred, 25);

    cvtColor(blurred, blurred, cv::COLOR_BGR2HSV);
    //cvtColor(blurred, blurred, cv::COLOR_BGR2YUV);

    Mat blurred_bw;
    inRange(blurred, Scalar(160, 80, 80), Scalar(190, 255, 255), blurred_bw);

    Mat blurred_mask;
    blurred.copyTo(blurred_mask, blurred_bw);
    //return blurred_mask;

    Mat gray, gray_blurred;
    cvtColor(blurred_mask, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray_blurred, 15);


    dilate(gray_blurred, gray_blurred, Mat(), Point(-1,-1));
    erode( gray_blurred, gray_blurred, Mat());
    return gray_blurred;
}

Mat filter::redBinderColor(Mat frame) {
    return frame;
}
