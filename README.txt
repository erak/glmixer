

                       GLMixer

                 Graphic Live Mixer
  Real-time video mixing software for live performance

                 By Bruno Herbelin


       https://sourceforge.net/projects/glmixer/
                    GPL3 LICENCE

ABOUT

GLMixer performs in real time the graphical blending of several movie clips.
You would typically load a set of video samples by drag'n drop, and decide on the fly
how much they should be visible, arrange the images in the screen, and which effects
you apply to them.

The principle of interaction is to drop video files into a workspace, and to move
them in a circular area to change their opacity ; if you selects two videos, moving
them together makes a fading transition, and this principle is generalized to any
number of videos. Direct interaction with the video icons allows you to be fast and reactive,
and to move and deform videos on screen.

The output of your operations is shown in the main rendering window, which should
for example be displayed full-screen on an external monitor or a projector, or can
be saved as a video file.


HELP

Wiki
http://sourceforge.net/projects/glmixer/

Tutorial videos
http://vimeo.com/album/2401475

DEPENDENCIES

To compile GLMixer you need;
subversion
cmake
Qt Version 4 (not Qt 5)
Libav (or ffmpeg)
OpenCV (optionnal)


COMPILATION GUIDELINES

  1. Install the dependencies

  2. Checkout GLMixer source files from https://sourceforge.net/p/glmixer/Source/HEAD/tree/.

        svn checkout svn://svn.code.sf.net/p/glmixer/Source/trunk glmixer-Source

     or download source from

        https://sourceforge.net/projects/glmixer/files/Linux/

  3. Create a folder for building (e.g. glmixer-Build)

  4. Run CMake GUI and select the GLMixer top directory as location of the source.
     Do **configure** (choose Ninja)
     Make sure there is no error and set '`CMAKE_BUILD_TYPE`' to '`Release`'
     Do **generate** with CMake.

  5. Compile : cd to the build folder, and run 'ninja' in a terminal to build the program (or use an IDE).


UNIX COMPILATION

     Open a terminal

     Go to the building directory
        $ cd glmixer-Build

     Run cmake command line to choose ninja generator.
        $ cmake -G Ninja ../glmixer-Source

     To be more specific, you might want to build a Release, ignore development warnings
     and use the optional features of OpenCV (web cam support) and FreeFrame (plugins):
        $ cmake -DCMAKE_BUILD_TYPE=Release -Wno-dev -DUSE_OPENCV=True -DUSE_UNDO=False -G Ninja ../

     If all goes well, it ends with :

        -- Configuring done
        -- Generating done
        -- Build files have been written to: XXX YOUR SOURCE PATH XXX

    Compile with ninja :
        $ ninja

     It should end with a message like (ignore warnings):

        [128/128] Linking CXX executable src/glmixer

     You can run the program directly :
        $ ./src/glmixer



LINUX COMPILATION

    Install programs and libraries (Ubuntu)

        $ sudo apt-get install subversion cmake-qt-gui ninja-build libqt4-opengl-dev libglew-dev libavformat-dev libhighgui-dev libavfilter-dev libv4l-dev xsltproc

    (This installs all necessary packages such as xsltproc, libqtcore4, libqtgui4, libqt4-xml, libqt4-opengl, qt4-qmake, libqt4-dev, libqt4-opengl-dev, libavcodec-dev, libswscale-dev, libavformat-dev, libavutil-dev, libavfilter-dev, libglew-dev, libvorbis-dev, libx264-dev, libxvidcore-dev, libv4l-dev, libcv-dev, libcvaux-dev, libhighgui-dev, libv4l-dev).

    You can now compile like under Unix (see above)


    To install it in your system, run cmake (as above but) with the following options :

        $ cmake -D CMAKE_BUILD_TYPE=RelWithDebInfo -D USE_OPENCV=True -D USE_FREEFRAMEGL=1.6 -D CMAKE_INSTALL_PREFIX=/usr -G Ninja ../glmixer-Source/

    After compiling the program (see above), build the debian package :

        $ cpack

    It hopefully ends with :

        CPack: - package: /home/[YOUR SOURCE PATH]/GLMixer_[version].deb generated.

    And you can now install it (use the filename generated above):

        $ sudo apt-get install /home/[YOUR SOURCE PATH]/GLMixer_[version].deb



OSX COMPILATION

Install home-brew

    Follow instructions from http://brew.sh/

Install programs and libraries (run the following in a terminal)

        brew install subversion
        brew install ninja
        brew install cmake
        brew install ffmpeg
        brew install qt4
        brew install glew
        brew install homebrew/science/opencv

You can now compile like under Unix (see above)



WINDOWS COMPILATION


Install msys2

    Follow instructions from https://msys2.github.io/

Install programs and x86_64 libraries (run the following in a terminal)

        pacman -S subversion
        pacman -S mingw-w64-x86_64-gcc
        pacman -S mingw-w64-x86_64-ninja
        pacman -S mingw-w64-x86_64-cmake
        pacman -S mingw-w64-x86_64-glew
        pacman -S mingw-w64-x86_64-qt4
        pacman -S mingw-w64-x86_64-opencv
        pacman -S mingw-w64-x86_64-ffmpeg

You can now compile like under Unix (see above)


