{
  "targets": [
    {
      "target_name": "addon",
      "sources": ["../../src/addon.cpp",
				  "../../../frc2522cv/src/detect.cpp",
				  "../../../frc2522cv/src/filter.cpp"
				  ], 
      "include_dirs": ["C:/opencv/build/include"],  
      "link_settings": {
                        'libraries':    ['C:/opencv/build/x64/vc14/lib/opencv_world310.lib']
                       }
    }
  ]
}