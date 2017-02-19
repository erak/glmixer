
cmake_minimum_required (VERSION 2.6)
project (SCREENMIX)

if( WIN32 )
    #--------------------------------------------------------------------------------
    # This SETs the windows build that will need the special winmain@16 call. Qt provides
    #  this for us in the qtmain.lib file. Using this cmake code will ensure we have it
    #  linked into our build. Not needed on Unix/OS X/Linux which is why we have the
    #  IF(WIN32) conditional.
    set(QT_USE_QTMAIN TRUE)

    # force Linker to link with / without console under Windows
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}  -mingw32 -Wl,-subsystem,console,--enable-auto-import")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mingw32 -Wl,-subsystem,windows,--enable-auto-import")
endif( WIN32 )

# add the corresponding path to include
include(${QT_USE_FILE})

#include the shared memory manager dir
include_directories(${LIBSHAREDMEMORYMANAGER_SOURCE_DIR} )

#include the current source dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# do the qt-cmake magic
qt4_add_resources(SCREENMIX_RCS_SRCS icons.qrc)

# tell cmake to create .moc files for all files that require such a file.
# note: this assumes that you use #include "header.moc" in your files
qt4_automoc( screencapture.cpp )

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(MINGW)
    # This sets up the exe icon for windows under mingw.
    set(SCREENMIX_RES_FILES "${CMAKE_SOURCE_DIR}/win/screenMix.rc")
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")

    add_executable(screenMix WIN32
                   screencapture.cpp
                   main.cpp
                   ${SCREENMIX_RCS_SRCS}
                   ${SCREENMIX_RES_FILES}
    )

else(MINGW)
    add_executable(screenMix
                   screencapture.cpp
                   main.cpp
                   ${SCREENMIX_RCS_SRCS}
    )
endif(MINGW)


target_link_libraries(screenMix SharedMemoryManager ${QT_LIBRARIES} )


if(WIN32)
    INSTALL(TARGETS screenMix RUNTIME DESTINATION bin COMPONENT Runtime)
endif(WIN32)
