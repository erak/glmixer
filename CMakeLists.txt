##
## CMake configuration
##
project(glmixer)
cmake_minimum_required(VERSION 2.8.0)
include(${CMAKE_SOURCE_DIR}/macros.cmake)

IF( MINGW )
macro(msys_to_cmake_path MsysPath ResultingPath)
  string(REGEX REPLACE "C:([^ ]*)"  "//c\\1" ${ResultingPath} "${MsysPath}")
endmacro()
ENDIF (MINGW)

# Use SVN to read repository version
IF(EXISTS "${CMAKE_SOURCE_DIR}/.svn")
    FIND_PACKAGE(Subversion)
    IF(Subversion_FOUND)
        IF( MINGW )
          msys_to_cmake_path(${CMAKE_SOURCE_DIR} CMAKE_SOURCE_DIR_MINGW )
          Subversion_WC_INFO( ${CMAKE_SOURCE_DIR_MINGW} GLMIXER)
        ELSE (MINGW)
          Subversion_WC_INFO( ${CMAKE_SOURCE_DIR} GLMIXER)
        ENDIF (MINGW)
        MESSAGE("Current subversion revision is ${GLMIXER_WC_REVISION}")
    ENDIF(Subversion_FOUND)
ENDIF()

set(GLMIXER_VERSION_MAJOR 1)
set(GLMIXER_VERSION_MINOR 5)
SET(GLMIXER_BINARY "glmixer")

# Expose CMAKE_INCLUDE_PATH and CMAKE_LIBARY_PATH to the GUI so users
# may set these values without needing to manipulate the environment.
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")

# Propose two build configurations
if(DEFINED CMAKE_BUILD_TYPE)
    # Default
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    endif(NOT CMAKE_BUILD_TYPE)

    set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo" )
endif()


if( APPLE )
    if(DEFINED CMAKE_OSX_ARCHITECTURES)
        # Default
        if(NOT CMAKE_OSX_ARCHITECTURES)
            set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE STRING "Choose compilation architecture." FORCE)
        endif(NOT CMAKE_OSX_ARCHITECTURES)

        set_property( CACHE CMAKE_OSX_ARCHITECTURES PROPERTY STRINGS "i386;x86_64" )
    endif()

    #set(CMAKE_OSX_TARGETS "10.5;10.6;10.7" CACHE STRING "Target OSX version (Min requirement)" FORCE)
    if(DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
        # Default
        if(NOT CMAKE_OSX_DEPLOYMENT_TARGET)
            set(CMAKE_OSX_DEPLOYMENT_TARGET "" CACHE STRING "Choose OSX Version for Deployment." FORCE)
        endif(NOT CMAKE_OSX_DEPLOYMENT_TARGET)

        set_property( CACHE CMAKE_OSX_DEPLOYMENT_TARGET PROPERTY STRINGS ";10.5;10.6;10.7;10.8;10.9;10.10;10.11;10.12" )
    endif()

endif( APPLE )

# avoid stupid cmake warning
IF(COMMAND CMAKE_POLICY)
    CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

##
## COMPILATION SETTINGS
##

IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# defines used by preprocessor to integrate program version and SVN revision into the application
add_definitions(-DGLMIXER_VERSION=${GLMIXER_VERSION_MAJOR}.${GLMIXER_VERSION_MINOR})
IF(GLMIXER_WC_REVISION)
    add_definitions(-DGLMIXER_REVISION=${GLMIXER_WC_REVISION})
ENDIF(GLMIXER_WC_REVISION)

##
## LIBRARIES
##

# Propose two library link modes> static or shared
set(GLMIXER_LINK_STATIC OFF CACHE BOOL "Preferably link with static libraries (when available)")

set( CMAKE_FIND_LIBRARY_SUFFIXES )
if( GLMIXER_LINK_STATIC )
    message(STATUS "Searching for static libraries preferably." )
    # set the possible suffix for library files in favor of static libs
    if( APPLE )
        set( CMAKE_FIND_LIBRARY_SUFFIXES .a .so .so.0 .dylib .framework)
    else( APPLE )
        if(WIN32)
                set( CMAKE_FIND_LIBRARY_SUFFIXES .a .lib .lib64 .dll.a .dll )
        else(WIN32)
                # not APPLE, not WIN32 ; must be unix !
                set( CMAKE_FIND_LIBRARY_SUFFIXES  .a .so .so.0 .so.1 )
        endif(WIN32)
    endif( APPLE )
else( GLMIXER_LINK_STATIC )
    message(STATUS "Searching for shared libraries preferably" )
    # set the possible suffix for library files in favor of dynamic libs
    if( APPLE )
        set( CMAKE_FIND_LIBRARY_SUFFIXES .so .so.0 .dylib .framework .a )
    else( APPLE)
        if( WIN32 )
                set( CMAKE_FIND_LIBRARY_SUFFIXES .dll.a .dll .lib .lib64 .a )
        else( WIN32 )
                # not APPLE, not WIN32 ; must be unix !
                set( CMAKE_FIND_LIBRARY_SUFFIXES  .so .so.0 .so.1 .a )
        endif( WIN32 )
    endif( APPLE )
endif( GLMIXER_LINK_STATIC )

set( CMAKE_LIBRARY_PATH
  /opt/local/lib
  /opt/lib
  /usr/local/lib
  /usr/lib
  /mingw/bin
  /mingw/lib
  /mingw32/bin
  /mingw32/lib
  /mingw32/i686-w64-mingw32/bin/
  /mingw32/i686-w64-mingw32/lib/
  ~/Library/Frameworks
  /System/Library/Frameworks
  ${CMAKE_SYSTEM_LIBRARY_PATH}
)


# HERE ARE THE BASIC DEPENDENCIES
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
set( DESIRED_QT_VERSION 4)
find_package( Qt REQUIRED)
find_package( OpenGL REQUIRED)
set( GLMIXER_LIBRARIES  ${OPENGL_LIBRARY})

find_package(Boost REQUIRED)
set( GLMIXER_LIBRARIES boost_system ${GLMIXER_LIBRARIES})


# find_library(FOUNDATION_LIBRARY Foundation REQUIRED)
# set( GLMIXER_LIBRARIES  ${GLMIXER_LIBRARIES}  ${FOUNDATION_LIBRARY})

# SOME HINTS FOR THE FIND_LIBRARY BELLOW
set( CMAKE_INCLUDE_PATH
  ${CMAKE_INCLUDE_PATH}
  /opt/local/include
  /opt/include
  /usr/local/include
  /usr/include
  /mingw/include
  ${CMAKE_SYSTEM_INCLUDE_PATH}
)

# HERE ARE THE OPTIONNAL MODULES TO COMPILE
SET(USE_SESSION_MANAGEMENT ON CACHE BOOL "CHECK to compile with Session switcher")
SET(USE_TAG_MANAGEMENT OFF CACHE BOOL "CHECK to compile with the Tag manager")
SET(USE_HISTORY_MANAGEMENT OFF CACHE BOOL "CHECK to compile with History manager")
SET(USE_UNDO ON CACHE BOOL "CHECK if you want to compile the Undo functionnality")

# HERE IS THE OPTIONNAL USE OF SHARED MEMORY
SET(USE_SHAREDMEMORY OFF CACHE BOOL "CHECK to compile with Shared Memory support")

if( USE_SHAREDMEMORY )

    add_subdirectory(SharedMemory)

    include_directories(${LIBSHAREDMEMORYMANAGER_SOURCE_DIR} )
    set(GLMIXER_LIBRARIES SharedMemoryManager ${GLMIXER_LIBRARIES} )
    message( STATUS "Using Shared Memory Manager library")

#    # HERE IS THE OPTIONNAL USE OF SPOUT
#    if( WIN32 )

#        set( USE_SPOUT BOOL OFF )
#        unset(SPOUT_INCLUDE CACHE)

#        # SPOUT library (http://spout.zeal.co/)
#        set(SPOUT_PATH "C:/Program Files (x86)/Spout" CACHE PATH "Please enter the path to the SpoutSDK folder (http://spout.zeal.co/).")

#        find_path( SPOUT_INCLUDE "spout.h" HINTS "${SPOUT_PATH}/Source/" )

#        if( SPOUT_INCLUDE )

#            add_subdirectory(libSpout)
#            set( USE_SPOUT BOOL ON )

#            include_directories(${SPOUT_INCLUDE} )
#            set(GLMIXER_LIBRARIES Spout ${GLMIXER_LIBRARIES} )
#            message( STATUS "Using Spout library")

#        endif( SPOUT_INCLUDE )

#    endif( WIN32 )

endif( USE_SHAREDMEMORY )


find_library( LOG4CPP_LIBRARY NAMES log4cpp )
set( GLMIXER_LIBRARIES ${GLMIXER_LIBRARIES} ${LOG4CPP_LIBRARY}  )
message(STATUS "log4cpp dependencies OK.")


# HERE IS THE OPTIONNAL INSTALLATION OF OPENCV
SET(USE_OPENCV ON CACHE BOOL "CHECK if you want to compile with OpenCV library")

if(USE_OPENCV)

message(STATUS "Looking for OpenCV.")

    unset(OPENCV_CORE_LIBRARY CACHE)
    unset(OPENCV_IMGPROC_LIBRARY CACHE)
    unset(OPENCV_HIGHGUI_LIBRARY CACHE)

    find_library( OPENCV_CORE_LIBRARY NAMES opencv_core cxcore200 opencv_core230 opencv_core2413)
    find_library( OPENCV_IMGPROC_LIBRARY NAMES opencv_imgproc cvaux200 opencv_imgproc2413)
    find_library( OPENCV_HIGHGUI_LIBRARY NAMES opencv_videoio opencv_highgui highgui200 opencv_highgui2413)
    # if we find the opencv libs required, then use opencv
    if(OPENCV_CORE_LIBRARY AND OPENCV_IMGPROC_LIBRARY AND OPENCV_HIGHGUI_LIBRARY)
        set( GLMIXER_LIBRARIES  ${GLMIXER_LIBRARIES} ${OPENCV_IMGPROC_LIBRARY} ${OPENCV_HIGHGUI_LIBRARY} ${OPENCV_CORE_LIBRARY})
        message(STATUS "Found OpenCV libraries (${OPENCV_IMGPROC_LIBRARY} ${OPENCV_HIGHGUI_LIBRARY} ${OPENCV_CORE_LIBRARY}).")

        if( APPLE )
            SET(USE_QUICKTIME ${USE_QUICKTIME} CACHE BOOL "CHECK if you want to compile with QuickTime library")

                if(USE_QUICKTIME)
                        find_package( QuickTime REQUIRED)
                        set( GLMIXER_LIBRARIES ${GLMIXER_LIBRARIES} ${QUICKTIME_LIBRARY} )
                        set(OSX_ARCHITECTURES "i386")
                        message(STATUS "Set the variable CMAKE_OSX_ARCHITECTURE to i386 because QuickTime is i386 only.")
                else(USE_QUICKTIME)
                        find_library( QTKIT_LIBRARY NAMES QTKit )
                        if(QTKIT_LIBRARY)
                                set( GLMIXER_LIBRARIES ${GLMIXER_LIBRARIES} ${QTKIT_LIBRARY} )
                                message(STATUS "Found QTKit framework.")
                        endif(QTKIT_LIBRARY)
                endif(USE_QUICKTIME)
                find_library( COCOA_LIBRARY NAMES Cocoa )
                find_library( QUARTZCORE_LIBRARY NAMES QuartzCore )
                if(COCOA_LIBRARY AND QUARTZCORE_LIBRARY)
                        set( GLMIXER_LIBRARIES ${GLMIXER_LIBRARIES} ${COCOA_LIBRARY} ${QUARTZCORE_LIBRARY}  )
                        message(STATUS "OpenCV OSX dependencies OK.")
                endif(COCOA_LIBRARY AND QUARTZCORE_LIBRARY)
        else( APPLE )
                if( UNIX )
                        find_library( V4L_LIBRARY NAMES v4l1 )
                        if(V4L_LIBRARY)
                                set( GLMIXER_LIBRARIES ${GLMIXER_LIBRARIES} ${V4L_LIBRARY}  )
                                message(STATUS "OpenCV UNIX dependencies OK.")
                        endif(V4L_LIBRARY)
                endif( UNIX )
        endif( APPLE )

    else(OPENCV_CORE_LIBRARY AND OPENCV_IMGPROC_LIBRARY AND OPENCV_HIGHGUI_LIBRARY)

        unset(USE_OPENCV CACHE)
 #       set(USE_OPENCV OFF CACHE BOOL)
 message(STATUS "Did not find OpenCV.")

    endif(OPENCV_CORE_LIBRARY AND OPENCV_IMGPROC_LIBRARY AND OPENCV_HIGHGUI_LIBRARY)

endif(USE_OPENCV)

if(USE_OPENCV)
        message(STATUS "Using OpenCV.")
endif(USE_OPENCV)


# HERE IS THE OPTIONNAL INSTALLATION OF FREEFRAMEGL

set(USE_FREEFRAMEGL "NO" CACHE STRING "Choose if you want to compile with FreeFrame GL library")
set_property(CACHE USE_FREEFRAMEGL PROPERTY STRINGS "NO;1.5;1.6")

if(USE_FREEFRAMEGL)

    SET(FREEFRAMEGL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libFreeFrameGL/FFGL-SDK-${USE_FREEFRAMEGL}")

    SET(FREEFRAMEGL_DIR_PLUGINS "${FREEFRAMEGL_PATH}/Source/FFGLPlugins/")
    SET(FREEFRAMEGL_DIR_HOST "${FREEFRAMEGL_PATH}/Source/FFGLHost/")

    include_directories("${FREEFRAMEGL_PATH}/Include" ${FREEFRAMEGL_DIR_PLUGINS} ${FREEFRAMEGL_DIR_HOST})

    if(UNIX)
        SET(GLMIXER_DEPENDENCIES ${GLMIXER_DEPENDENCIES} dl)
    endif(UNIX)

endif(USE_FREEFRAMEGL)


SET(USE_NVIDIA_CUDA OFF CACHE BOOL "CHECK to compile with NVIDIA CUDA Video Decoding")

if(USE_NVIDIA_CUDA)

    find_package(CUDA REQUIRED)

    # Found CUDA package
    if(CUDA_VERSION)
        #
        # Search for libnvcuvid.so in NVidia drivers (not in the package)
        #
        # Query nvidia-settings for the version string
        execute_process(COMMAND nvidia-settings -q 0/NvidiaDriverVersion OUTPUT_VARIABLE NVIDIA_DRIVER_STRING OUTPUT_STRIP_TRAILING_WHITESPACE)
        # make a list of the string
        separate_arguments(NVIDIA_DRIVER_STRING)
        # get the last element of the list (e.g. 361.42)
        list(GET NVIDIA_DRIVER_STRING -1 NVIDIA_DRIVER_VERSION)
        # keep only the major version (e.g. replace '.42' by empty string)
        string(REGEX REPLACE "\\.[0-9]+" "" NVIDIA_DRIVER_MAJOR_VERSION ${NVIDIA_DRIVER_VERSION})
        # suggest the path where to find the library (e.g. /usr/lib/nvidia-361)
        string(CONCAT NVIDIA_DRIVER_PATH "/usr/lib/nvidia-" ${NVIDIA_DRIVER_MAJOR_VERSION})
        # find the library in the given driver path
        find_library(NVIDIA_NVCUVID_LIBRARY NAMES nvcuvid PATHS ${NVIDIA_DRIVER_PATH})
        if(NVIDIA_NVCUVID_LIBRARY)
         message( STATUS "Found nvcuvid: " ${NVIDIA_NVCUVID_LIBRARY})
        endif(NVIDIA_NVCUVID_LIBRARY)

        # put together all CUDA Libraries (for linker)
        SET(CUDA_LIBRARIES ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY} ${NVIDIA_NVCUVID_LIBRARY} )

        # Enter libCUDADecoder to compile it
        add_subdirectory(libCUDADecoder)

    else (CUDA_VERSION)
        unset(USE_NVIDIA_CUDA CACHE)
    endif(CUDA_VERSION)

endif(USE_NVIDIA_CUDA)

if(USE_NVIDIA_CUDA)
        message(STATUS "Using Nvidia CUDA version ${CUDA_VERSION}")
endif(USE_NVIDIA_CUDA)

# HERE ARE THE FFMPEG ESSENTIAL AND REQUIRED LIBRARIES

SET(GLMIXER_DEPENDENCIES ${GLMIXER_DEPENDENCIES} avformat avcodec avutil swscale avfilter x264)

FOREACH(GLMIXER_DEPENDENCY ${GLMIXER_DEPENDENCIES})
    STRING(TOUPPER ${GLMIXER_DEPENDENCY} _upper_glmixer_dependency)
    unset(${_upper_glmixer_dependency}_LIBRARY CACHE)
    find_library(${_upper_glmixer_dependency}_LIBRARY ${GLMIXER_DEPENDENCY})
        if(${_upper_glmixer_dependency}_LIBRARY)
                set( GLMIXER_LIBRARIES  ${GLMIXER_LIBRARIES} ${${_upper_glmixer_dependency}_LIBRARY} )
                message( STATUS "Found ${GLMIXER_DEPENDENCY}: ${${_upper_glmixer_dependency}_LIBRARY}")
        else(${_upper_glmixer_dependency}_LIBRARY)
            message( FATAL_ERROR "${GLMIXER_DEPENDENCY} library NOT found but required.")
        endif(${_upper_glmixer_dependency}_LIBRARY)
ENDFOREACH(GLMIXER_DEPENDENCY)


# BELLOW IS THE LIST OF FFMPEG OPTIONNAL DEPENDENCIES.
# ADD THE LIBRARIES AS REQUIRED BY YOUR INSTALLATION OF FFMPEG

SET(GLMIXER_UTILITIES avcore pthread theora modplug theoraenc theoradec xvidcore faac gsm
                      mp3lame vorbis vorbisenc ogg orc-0.4 schroedinger-1.0 va png14
                      speex dirac_encoder jpeg vpx bz2 z)

FOREACH(GLMIXER_UTILITY ${GLMIXER_UTILITIES})
    STRING(TOUPPER ${GLMIXER_UTILITY} _upper_glmixer_utility)
    # unset the variable to force the search for the library
    unset(${_upper_glmixer_utility}_LIBRARY CACHE)
    find_library(${_upper_glmixer_utility}_LIBRARY ${GLMIXER_UTILITY})
        if(${_upper_glmixer_utility}_LIBRARY)
            set( GLMIXER_LIBRARIES  ${GLMIXER_LIBRARIES} ${${_upper_glmixer_utility}_LIBRARY} )
            message( STATUS "Found ${GLMIXER_UTILITY}: ${${_upper_glmixer_utility}_LIBRARY}")
        endif(${_upper_glmixer_utility}_LIBRARY)
ENDFOREACH(GLMIXER_UTILITY)

# HERE IS THE INSTALLATION OF WIN32 SOCK LIB

if(WIN32)
    # HERE IS THE INSTALLATION WIN32 SOCK LIB
    set( GLMIXER_LIBRARIES  ${GLMIXER_LIBRARIES} -lws2_32 )
endif(WIN32)


# HERE IS THE GLEW DEPENDENCY

unset(GLEW_LIBRARY CACHE)
find_library( GLEW_LIBRARY NAMES GLEW glew glew32)
if(GLEW_LIBRARY)
  set( GLMIXER_LIBRARIES  ${GLMIXER_LIBRARIES} ${GLEW_LIBRARY} )
  find_path( GLEW_INCLUDE NAMES GL/glew.h )
  include_directories(${GLEW_INCLUDE})
  message( STATUS "Found GLEW: ${GLEW_LIBRARY}.")
else(GLEW_LIBRARY)
  message(FATAL_ERROR "GLEW library NOT found but required.")
endif(GLEW_LIBRARY)

##
## tell cmake to process CMakeLists.txt in those subdirectories
##

add_subdirectory(libQtProperty)
add_subdirectory(libQtColorPicker)
add_subdirectory(libOSCPack)

if(USE_FREEFRAMEGL)
    message( STATUS "Using FreeFrameGL")
    add_subdirectory(${FREEFRAMEGL_PATH})
    add_subdirectory(FreeFramePlugins)
endif(USE_FREEFRAMEGL)

add_subdirectory(src)
