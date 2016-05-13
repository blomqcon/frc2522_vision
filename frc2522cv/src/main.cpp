#include <iostream>

//#include "../include/camera.h"
#include "../include/detect.h"
#include "../include/filter.h"

using namespace std;
using namespace cv;
using namespace frc2522cv;

int main() {
	Mat frame;
    Mat original;
    VideoCapture webcam = VideoCapture(0);
    while(true) {
		webcam >> frame;
		frame.copyTo(original);

        Target target = Target();
        Mat binary = filter::binary(frame, filter::HSV, Scalar(150.0, 100.0, 110.0), Scalar(200.0, 255.0, 255.0));
        Mat blobs = detect::showScreenLocation(binary, target, detect::SimpleBlob);

        Point2d largestBlob = detect::targetScreenLocation(binary, target, detect::SimpleBlob);
        printf("(%f, %f\n", largestBlob.x, largestBlob.y);

        imshow("filter", blobs);
        imshow("original", original);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}
