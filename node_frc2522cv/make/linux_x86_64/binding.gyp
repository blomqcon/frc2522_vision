{
  "targets": [
    {
      "target_name": "addon",
      "sources": ["../src/addon.cpp"], 
      "include_dirs": ["/usr/local/include/", "../include/"],  
      "link_settings": {
                        'libraries':    ['-lopencv_core -lopencv_features2d -lopencv_contrib -lopencv_imgproc'],
                        'library_dirs': ['/usr/local/lib', "../../frc2522/make/linux_x86_64/Release"],
                       }
    }
  ]
}