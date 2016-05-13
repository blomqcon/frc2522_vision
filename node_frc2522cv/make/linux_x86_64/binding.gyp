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
                            "/usr/local/lib/libopencv_videoio.so",
                            "/usr/local/lib/libopencv_superres.so",
                            "/usr/local/lib/libopencv_shape.so",
                            "/usr/local/lib/libopencv_highgui.so",
                            "/usr/local/lib/libopencv_videostab.so",
                            "/usr/local/lib/libopencv_video.so",
                            "/usr/local/lib/libopencv_flann.so",
                            "/usr/local/lib/libopencv_objdetect.so",
                            "/usr/local/lib/libopencv_stitching.so",
                            "/usr/local/lib/libopencv_photo.so",
                            "/usr/local/lib/libopencv_imgcodecs.so",
                            "/usr/local/lib/libopencv_ml.so",
                            "/usr/local/lib/libopencv_features2d.so",
                            "/usr/local/lib/libopencv_calib3d.so",
                            "/usr/local/lib/libopencv_ts.a",
                            "/usr/local/lib/libopencv_core.so",
                            "/usr/local/lib/libopencv_imgproc.so"
                        ],
                        'library_dirs': ['/usr/local/lib']
                       }
    }
  ]
}