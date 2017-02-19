
cmake_minimum_required (VERSION 2.8)
project (LIBFFGLTEST)

if(WIN32)
  add_library(fftest SHARED FreeFrameTest.cpp)
else(WIN32)
  add_library(fftest MODULE FreeFrameTest.cpp)
endif(WIN32)


if(APPLE)
target_link_libraries(fftest -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY})
else(APPLE)
target_link_libraries(fftest -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY})
endif(APPLE)
