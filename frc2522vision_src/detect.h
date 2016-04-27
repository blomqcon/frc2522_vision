#ifndef DETECT_H
#define DETECT_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>


namespace frc2522cv {
    using namespace cv;
    namespace detect {
        Mat showRedBinderBlob(Mat frame, Mat bw);
        Point2d redBinderBlob(Mat frame);
        Mat redBinderBoundingBlob(Mat frame);
        Mat redBinderContour(Mat frame);
        Mat redBinderHough(Mat frame);
	    double getTargetLocation(double a, double b);
    }
}



#endif // DETECT_H
