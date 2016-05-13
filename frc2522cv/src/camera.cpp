 #include "../include/camera.h"

 using namespace cv;

namespace frc2522cv {
    Mat camera::getDefaultFrame() {
		//if (!cap.isOpened()) //error
        Mat frame;
        webcam >> frame;
        return frame;
    }

    Mat camera::getWebFrame() {
		Mat frame;
		ipcam >> frame;
		return frame;
    }

     Mat camera::getVideoFrame(std::string video, int i) {
 		Mat frame;
 		testVid >> frame;
 		if (frame.empty()) {
 			testVid.release();
 			testVid.open("../../_test_clips/medium_room.avi");
 			testVid >> frame;
 		}
 		return frame;
     }
}
