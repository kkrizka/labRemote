# Check for OpenCV
find_package( OpenCV QUIET )

if ( ${OpenCV_FOUND} )
  # Add the headers
  include_directories( include )

  # Add all *.c* files as source code
  file(GLOB SrcFiles *.c*)
  add_library(ImageRec SHARED ${SrcFiles}) 
  target_link_libraries(ImageRec ${OpenCV_LIBS})
else()
  message("Disabling libImageRec due to missing OpenCV")
endif()
