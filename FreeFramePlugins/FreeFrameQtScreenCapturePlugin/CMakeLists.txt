
cmake_minimum_required (VERSION 2.8)
project (LIBFFGLQTSCREENCAPTURE)

# add the corresponding path to include
include(${QT_USE_FILE})

if(WIN32)
  add_library(ffglQtScreenCapture SHARED FreeFrameQtScreenCapture.cpp)
else(WIN32)
  add_library(ffglQtScreenCapture MODULE FreeFrameQtScreenCapture.cpp)
endif(WIN32)


if(APPLE)
target_link_libraries(ffglQtScreenCapture -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY} ${QT_LIBRARIES})
else(APPLE)
target_link_libraries(ffglQtScreenCapture -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY} ${QT_LIBRARIES})
endif(APPLE)
