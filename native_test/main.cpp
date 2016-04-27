#include <iostream>

#include "../frc2522vision_src/camera.h"
#include "../frc2522vision_src/filter.h"
#include "../frc2522vision_src/detect.h"

using namespace std;
using namespace frc2522cv;

int main() {
    VideoCapture cap("../test_clips/medium_room.avi");
    //VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    Mat frame;
    Mat original;
    while(true) {
        frame = getDefaultFrame(cap);
        frame.copyTo(original);
        if (frame.empty()) {
            cap.release();
            cap.open("medium_room.avi");
            continue;
        }

        Mat gray = filter::redBinderBinary(frame);
        Mat blobs = detect::showRedBinderBlob(original, gray);
        Point2d largestBlob = detect::redBinderBlob(gray);
        printf("(%f, %f)\n", largestBlob.x, largestBlob.y);

        imshow("filter", blobs);
        imshow("original", original);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}
