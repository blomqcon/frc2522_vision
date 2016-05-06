{
  "targets": [
    {
      "target_name": "addon",
      "sources": ["../../src/addon.cpp"], 
      "include_dirs": ["C:\Program Files\OpenCV\build\include", "../include/"],  
      "link_settings": {
                        'libraries':    ['-lopencv_core -lopencv_features2d -lopencv_contrib -lopencv_imgproc'],
                        'library_dirs': ['C:\Program Files\OpenCV\build\x86\vc12\lib', "../../frc2522/make/windows_x86_64/Release"],
                       }
    }
  ]
}