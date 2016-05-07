{
  "targets": [
    {
      "target_name": "addon",
      "sources": ["../../src/addon.cpp",
				  "../../../frc2522cv/src/detect.cpp",
				  "../../../frc2522cv/src/filter.cpp",
				  "../../../frc2522cv/src/camera.cpp"
				  ], 
      "include_dirs": ["C:/Program Files/OpenCV/build/include"],  
      "link_settings": {
                        'libraries':    ['C:/Program Files/OpenCV/build/x64/vc12/lib/opencv_ts300.lib', 'C:/Program Files/OpenCV/build/x64/vc12/lib/opencv_world300.lib']
                       }
    }
  ]
}