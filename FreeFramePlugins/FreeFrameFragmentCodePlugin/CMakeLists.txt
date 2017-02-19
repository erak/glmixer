
cmake_minimum_required (VERSION 2.8)
project (LIBSHADERTOY)

if(WIN32)
  add_library(ShadertoyEffect SHARED FreeFrameShadertoyEffect.cpp FreeFrameFragmentCodePlugin.cpp )
  add_library(ShadertoySource SHARED FreeFrameShadertoySource.cpp FreeFrameFragmentCodePlugin.cpp )
else(WIN32)
  add_library(ShadertoyEffect MODULE FreeFrameShadertoyEffect.cpp FreeFrameFragmentCodePlugin.cpp )
  add_library(ShadertoySource MODULE FreeFrameShadertoySource.cpp FreeFrameFragmentCodePlugin.cpp )
endif(WIN32)

message( STATUS "Using ShadertoyEffect and ShadertoySource")

if(APPLE)

  set( CMAKE_FIND_LIBRARY_SUFFIXES .a )
  find_library( GLEW_LIBRARY_STATIC NAMES GLEW glew glew32)

  target_link_libraries(ShadertoyEffect -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY} ${GLEW_LIBRARY_STATIC})
  target_link_libraries(ShadertoySource -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY} ${GLEW_LIBRARY_STATIC})

else(APPLE)

  target_link_libraries(ShadertoyEffect -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
  target_link_libraries(ShadertoySource -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

endif(APPLE)
