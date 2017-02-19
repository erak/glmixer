
cmake_minimum_required (VERSION 2.8)
project (LIBV4LFFGL)

SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}" )

find_library( V4L2_LIBRARY NAMES v4l2)
find_library( V4L_CONVERT_LIBRARY NAMES v4lconvert)
find_library( PTHREAD_LIBRARY pthread)

if(V4L2_LIBRARY AND V4L_CONVERT_LIBRARY AND PTHREAD_LIBRARY)
    add_library(ffglVideo4Linux MODULE v4lFFGL.cpp)
   target_link_libraries(ffglVideo4Linux -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive   ${V4L2_LIBRARY} ${V4L_CONVERT_LIBRARY} ${PTHREAD_LIBRARY})
else()
    message(WARNING "ffglVideo4Linux not compiled because of missing dependeny.")
endif()

