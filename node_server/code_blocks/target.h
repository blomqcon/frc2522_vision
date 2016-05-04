#ifndef TARGET_H
#define TARGET_H

#include <vector>
#include <opencv2/opencv.hpp>

namespace frc2522cv {}
    class Target {
        public:
            Target();
            int cameraWidth;
            int cameraHeight;
            vector<Point3i> zeroPoints;

            Point3i getCenter();

            //Checks relative size and aspect ratios to determine where you must be
            //Assumes foundTarget is the target.
            cv::Point3i location(Target foundTarget);
    }
}



#endif // TARGET_H

