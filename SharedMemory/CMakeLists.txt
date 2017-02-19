cmake_minimum_required(VERSION 2.6)
PROJECT(LIBSHAREDMEMORYMANAGER)


# add the corresponding path to include
include(${QT_USE_FILE})

ADD_LIBRARY(SharedMemoryManager
            SharedMemoryManager.h
            SharedMemoryManager.cpp 
)


add_subdirectory(ScreenMix)
add_subdirectory(ScribbleMix)


