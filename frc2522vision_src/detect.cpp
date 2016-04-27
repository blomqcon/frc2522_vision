
#include "detect.h"

using namespace std;
using namespace frc2522cv;

double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

Mat detect::showRedBinderBlob(Mat frame, Mat bw) {
    SimpleBlobDetector::Params params;
    //params.minDistBetweenBlobs = 10.0f;
    //params.minThreshold = 100;
    //params.maxThreshold = 255;
    //params.thresholdStep = 10;

    params.minDistBetweenBlobs = 100.0f;  // minimum 10 pixels between blobs
    params.filterByColor = false;
    params.filterByCircularity = false;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.filterByArea = true;
    params.minArea = 10.0f;
    params.maxArea = 99999999.9f;
    params.minRepeatability = 1;

    SimpleBlobDetector blob_detector(params);

    std::vector<cv::KeyPoint> keypoints;
    blob_detector.detect(bw, keypoints);

    Mat frame_blobs;
    drawKeypoints(bw, keypoints, frame_blobs, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
    return frame_blobs;
    return frame;
}

Point2d detect::redBinderBlob(Mat frame_bw) {
    SimpleBlobDetector::Params params;
    params.minDistBetweenBlobs = 100.0f;  // minimum 10 pixels between blobs
    params.filterByColor = false;
    params.filterByCircularity = false;
    params.filterByArea = true;
    params.minArea = 10.0f;
    params.maxArea = 99999999.9f;
    params.minRepeatability = 1;

    std::vector<cv::KeyPoint> keypoints;
    SimpleBlobDetector blob_detector(params);
    blob_detector.detect(frame_bw, keypoints);
    cout << keypoints.size() << endl;
    if(keypoints.size() > 0) {
        KeyPoint largestKeyPoint = keypoints[0];
        for(int i = 1; i < keypoints.size(); i++) {
            if(keypoints[i].size > largestKeyPoint.size) {
                largestKeyPoint = keypoints[i];
            }
        }
        return largestKeyPoint.pt;
    } else {
        return Point2d(-1, -1);
    }
}

Mat detect::redBinderBoundingBlob(Mat frame) {
    return frame;
}

Mat detect::redBinderContour(Mat gray_frame) {
    Mat edges;
    Canny(gray_frame, edges, 10, 20, 3);
    // Dilate helps to remove potential holes between edge segments
    //dilate(gray, gray, Mat(), Point(-1,-1));
    int dilate_size = 10;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * dilate_size + 1, 2 * dilate_size + 1), Point(dilate_size, dilate_size));
    dilate(edges, edges, element);

    int erosion_size = 3;
    element = getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
    erode(edges, edges, element);

    Mat gray_color;
    cvtColor(gray_frame, gray_color, COLOR_GRAY2BGR);
    //threshold(gray0, gray0, 0, 255, THRESH_BINARY | THRESH_OTSU);


    std::vector<std::vector<Point> > contours;
    std::vector<std::vector<Point> > squares;
    findContours(edges, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    // Test contours
    std::vector<Point> approx;
    for (int i = 0; i < contours.size(); i++) {

        // approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
        //if(approx.size() >= 3 && approx.size() <= 6) {
        if(approx.size() >= 3 && approx.size() <= 6) {

            double maxCosine = 0;
            for (int j = 0; j < approx.size() + 1; j++) {
                    double cosine = fabs(angle(approx[j%approx.size()], approx[j-2], approx[j-1]));
                    //double cosine = fabs(angle(approx[j], approx[j+1], approx[j+2]));
                    maxCosine = MAX(maxCosine, cosine);
            }

            if (maxCosine < 0.3)
                    squares.push_back(approx);
            }

            /*if (approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx))) {
                    double maxCosine = 0;

                    for (int j = 2; j < 5; j++) {
                            double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                            maxCosine = MAX(maxCosine, cosine);
                    }

                    if (maxCosine < 0.3)
                            squares.push_back(approx);
            }*/
        }

        for ( int i = 0; i< squares.size(); i++ ) {
            // draw contour
            drawContours(gray_color, contours, i, Scalar(255,0,0), 5, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
        }

        return gray_color;
}

Mat detect::redBinderHough(Mat gray_frame) {

    Mat edges;
    Canny(gray_frame, edges, 100, 500, 3);

    #if 1
        std::vector<Vec2f> lines;
        //HoughLines(edges, lines, 1, CV_PI/180, 100, 0, 0 );
        HoughLines(edges, lines, 1, CV_PI/15, 20, 0, 0 );

        for( size_t i = 0; i < lines.size(); i++ ) {
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line(gray_frame, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
        }
         #else
              vector<Vec4i> lines;
              HoughLinesP(edges, lines, 1, CV_PI/180, 50, 50, 10 );
              for( size_t i = 0; i < lines.size(); i++ )
              {
                Vec4i l = lines[i];
                line( yellow_frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
              }
         #endif
    return gray_frame;
}







//////////////
double detect::getTargetLocation(double a, double b) {
    return a + b + 100;
}
