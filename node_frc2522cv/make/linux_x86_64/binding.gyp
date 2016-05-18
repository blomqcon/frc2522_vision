{
  "targets": [
    {
      "target_name": "addon",
      "sources": ["../../src/addon.cpp",
          "../../../frc2522cv/src/detect.cpp",
          "../../../frc2522cv/src/filter.cpp"
          ], 
      "include_dirs": ["/usr/local/include/"],  
      "link_settings": {
                        'libraries':    [
                            "/usr/local/arm-linux-gnueabihf/libopencv_highgui.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_photo.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_imgcodecs.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_ml.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_features2d.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_calib3d.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_ts.a",
                            "/usr/local/arm-linux-gnueabihf/libopencv_core.so",
                            "/usr/local/arm-linux-gnueabihf/libopencv_imgproc.so"
                        ],
                        'library_dirs': ['/usr/local/lib']
                       }
    }
  ]
}