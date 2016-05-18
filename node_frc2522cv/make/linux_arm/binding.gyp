{
  "targets": [
    {
      "target_name": "addon",
      "sources": ["../../src/addon.cpp",
          "../../../frc2522cv/src/detect.cpp",
          "../../../frc2522cv/src/filter.cpp"
          ], 
      "include_dirs": ["/root/opencv-arm/opencv/build/Release/install/lib/include/"],  
      "link_settings": {
                        'libraries':    [
                            "/root/opencv-arm/opencv/build/Release/install/lib/libopencv_core.so",
                            "/root/opencv-arm/opencv/build/Release/install/lib/libopencv_highgui.so",
                            "/root/opencv-arm/opencv/build/Release/install/lib/libopencv_imgproc.so",
                            "/root/opencv-arm/opencv/build/Release/install/lib/libopencv_features2d.so"
                        ]
                       }
    }
  ]
}