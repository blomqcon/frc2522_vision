{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "custom_module/addon.cpp", 
      				"../frc2522vision_src/detect.cpp"
      ], 
      "include_dirs": [ "/usr/local/include/" ],  
      "link_settings": {
                        'libraries':    ['-lopencv_core -lopencv_features2d -lopencv_contrib -lopencv_imgproc'],
                        'library_dirs': ['/usr/local/lib'],
                       }
    }
  ]
}