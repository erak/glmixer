# the next line SETs up include and link directories and defines some variables that we will use.

# this application uses QT with the following modules:
SET(QT_USE_QTOPENGL  TRUE)
SET(QT_USE_QTXML     TRUE)
SET(QT_USE_QTSVG     TRUE)
SET(QT_USE_QTNETWORK    TRUE)
SET(QT_USE_QTWEBKIT    TRUE)


if( WIN32 )
    #--------------------------------------------------------------------------------
    # This SETs the windows build that will need the special winmain@16 call. Qt provides
    #  this for us in the qtmain.lib file. Using this cmake code will ensure we have it
    #  linked into our build. Not needed on Unix/OS X/Linux which is why we have the
    #  IF(WIN32) conditional.
    set(QT_USE_QTMAIN TRUE)

    # force Linker to link with / without console under Windows
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,-subsystem,console,--enable-auto-import")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,-subsystem,windows,--enable-auto-import")
endif( WIN32 )

# add the corresponding path to include
include(${QT_USE_FILE})

# the variable "GLMIXER_SRCS" contains all .cpp files of this project
SET(GLMIXER_SRCS
    common.cpp
    glRenderWidget.cpp
    VideoFileDialogPreview.cpp
    VideoFileDialog.cpp
    VideoFileDisplayWidget.cpp
    VideoPicture.cpp
    VideoFile.cpp
    ProtoSource.cpp
    Source.cpp
    CloneSource.cpp
    VideoSource.cpp
    CaptureSource.cpp
    SvgSource.cpp
    WebSource.cpp
    RenderingSource.cpp
    AlgorithmSource.cpp
    AlgorithmSelectionDialog.cpp
    SourceDisplayWidget.cpp
    View.cpp
    MixerView.cpp
    GeometryView.cpp
    LayersView.cpp
    RenderingView.cpp
    CatalogView.cpp
    ViewRenderWidget.cpp
    SelectionManager.cpp
    RenderingManager.cpp
    RenderingEncoder.cpp
    OutputRenderWindow.cpp
    PropertyBrowser.cpp
    SourcePropertyBrowser.cpp
    SpringCursor.cpp
    DelayCursor.cpp
    AxisCursor.cpp
    LineCursor.cpp
    FuzzyCursor.cpp
    UserPreferencesDialog.cpp
    GammaLevelsWidget.cpp
    glmixer.cpp
    glmixerdialogs.cpp
    main.cpp
    video_rec.c
    testbuttonframe.cpp
    testwheelframe.cpp
    MixingToolboxWidget.cpp
    LayoutToolboxWidget.cpp
    OpenSoundControlManager.cpp
    NewSourceDialog.cpp
    WebSourceCreationDialog.cpp
    SessionSwitcher.cpp
    Tag.cpp
    CodecManager.cpp
    VideoStream.cpp
    VideoStreamSource.cpp
    VideoStreamDialog.cpp
    SizeSelectionWidget.cpp
    output_stream.cpp
)


if(WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../win/style.qrc.in ${CMAKE_CURRENT_BINARY_DIR}/style.qrc)
else(WIN32)
    if(APPLE)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../osx/style.qrc.in ${CMAKE_CURRENT_BINARY_DIR}/style.qrc)
    else(APPLE)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../linux/style.qrc.in ${CMAKE_CURRENT_BINARY_DIR}/style.qrc)
    endif(APPLE)
endif(WIN32)

SET(GLMIXER_RCS
    ../icons.qrc
    ../textures.qrc
    ../images.qrc
    ../opengl.qrc
    ../fonts.qrc
    ${CMAKE_CURRENT_BINARY_DIR}/style.qrc
)


SET(GLMIXER_UIS
    glmixer.ui
    VideoFileDialog.ui
    AlgorithmSelectionDialog.ui
    UserPreferencesDialog.ui
    GammaLevelsDialog.ui
    MixingToolboxWidget.ui
    LayoutToolboxWidget.ui
    NewSourceDialog.ui
    WebSourceCreationDialog.ui
    VideoStreamDialog.ui
    SizeSelectionWidget.ui
)


SET(USE_LOG_MANAGEMENT ON CACHE BOOL "CHECK to compile with the Logger")
if(USE_LOG_MANAGEMENT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_LOGS" )
    add_definitions(-DGLM_LOGS)
    message( STATUS "Using Log Management")
endif(USE_LOG_MANAGEMENT)

# if Use UNdO was set
if(USE_UNDO)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_UNDO" ) # make QtCreator happy
    add_definitions(-DGLM_UNDO)
    SET(GLMIXER_SRCS  ${GLMIXER_SRCS}
        UndoManager.cpp
    )
    message( STATUS "Using Undo")
endif(USE_UNDO)

# If SharedMemory was set, then link with its source files
if(USE_SHAREDMEMORY)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_SHM" )
    add_definitions(-DGLM_SHM)
    SET(GLMIXER_SRCS  ${GLMIXER_SRCS}
        SharedMemorySource.cpp
    )
endif(USE_SHAREDMEMORY)

if( USE_SPOUT )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_SPOUT" )
    add_definitions(-DGLM_SPOUT)
    SET(GLMIXER_SRCS  ${GLMIXER_SRCS}
        SpoutSource.cpp
    )
endif( USE_SPOUT )

# the GUI for shared memory is shared for SHM and SPOUT
if( USE_SHAREDMEMORY OR USE_SPOUT )
    SET(GLMIXER_SRCS  ${GLMIXER_SRCS}
        SharedMemoryDialog.cpp
    )
    SET(GLMIXER_UIS  ${GLMIXER_UIS}
        SharedMemoryDialog.ui
    )
endif( USE_SHAREDMEMORY OR USE_SPOUT )


# If FreeframeGL was set, then link with its source files
if(USE_FREEFRAMEGL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FFGL" ) # make QtCreator happy
    add_definitions(-DGLM_FFGL)
    add_definitions(-DFFGLPATH="${CMAKE_INSTALL_PREFIX}/lib/${GLMIXER_BINARY}/")

    SET( GLMIXER_SRCS  ${GLMIXER_SRCS}
        FFGLPluginInstances.cpp
        FFGLPluginSourceStack.cpp
        FFGLPluginSource.cpp
        FFGLPluginBrowser.cpp
        FFGLSource.cpp
        FFGLSourceCreationDialog.cpp
        FFGLEffectSelectionDialog.cpp
        FFGLPluginSourceShadertoy.cpp
        GLSLCodeEditor.cpp
        GLSLCodeEditorWidget.cpp
        GLSLSyntaxHighlighter.cpp
    )

    SET_SOURCE_FILES_PROPERTIES(FFGLPluginInstances.cpp PROPERTIES COMPILE_FLAGS -fno-strict-aliasing )

    SET(GLMIXER_UIS  ${GLMIXER_UIS}
        GLSLCodeEditorWidget.ui
        FFGLSourceCreationDialog.ui
        FFGLEffectSelectionDialog.ui
    )

    SET(GLMIXER_RCS  ${GLMIXER_RCS}
        ${CMAKE_CURRENT_BINARY_DIR}/../FreeFramePlugins/plugins.qrc
    )

    SET(GLMIXER_LIBRARIES FreeFrameGL ${GLMIXER_LIBRARIES} )

endif(USE_FREEFRAMEGL)

# If this application will use OpenCV
if(USE_OPENCV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_OPENCV" ) # make QtCreator happy
    add_definitions(-DGLM_OPENCV)
    SET( GLMIXER_SRCS  ${GLMIXER_SRCS}
        OpencvSource.cpp
        CameraDialog.cpp
    )

    SET(GLMIXER_UIS  ${GLMIXER_UIS}
        CameraDialog.ui
    )
endif(USE_OPENCV)

# if we use CUDA
if(USE_NVIDIA_CUDA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_CUDA" ) # make QtCreator happy
    add_definitions(-DGLM_CUDA)
    include_directories(${LIBCUDADECODER_SOURCE_DIR} )
    SET( GLMIXER_SRCS  ${GLMIXER_SRCS}
        CUDAVideoFile.cpp
    )
    message( STATUS "Using CUDA")
endif(USE_NVIDIA_CUDA)

# if we use V4l2
include_directories(${LIBV4L2CPP_SOURCE_DIR}/inc )

# if History Management was set
if(USE_HISTORY_MANAGEMENT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_HISTORY" ) # make QtCreator happy
    add_definitions(-DGLM_HISTORY)
    SET( GLMIXER_SRCS  ${GLMIXER_SRCS}
        HistoryManager.cpp
        HistoryManagerWidget.cpp
    )
    message( STATUS "Using History Management")
endif(USE_HISTORY_MANAGEMENT)

# if Session Management was set
if(USE_SESSION_MANAGEMENT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_SESSION" ) # make QtCreator happy
    add_definitions(-DGLM_SESSION)
    SET( GLMIXER_SRCS  ${GLMIXER_SRCS}
        SessionSwitcherWidget.cpp
    )
    message( STATUS "Using Session Management")
endif(USE_SESSION_MANAGEMENT)

# if Tags Management was set
if(USE_TAG_MANAGEMENT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_TAG" ) # make QtCreator happy
    add_definitions(-DGLM_TAG)
    SET( GLMIXER_SRCS  ${GLMIXER_SRCS}
        TagsManager.cpp
    )
    SET(GLMIXER_UIS  ${GLMIXER_UIS}
        TagsManager.ui
    )
    message( STATUS "Using Tag Management")
endif(USE_TAG_MANAGEMENT)


#include the current source dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# do the qt-cmake magic
qt4_wrap_ui(GLMIXER_UIS_H ${GLMIXER_UIS})
qt4_add_resources(GLMIXER_RCS_SRCS ${GLMIXER_RCS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# this application uses the libraries QtProperty and QtColorPicker
include_directories(${LIBQTPROPERTY_SOURCE_DIR} ${LIBQTCOLORPICKER_SOURCE_DIR} ${LIBOSCPACK_SOURCE_DIR} ${LIBV4L2_SOURCE_DIR})

# tell cmake to create .moc files for all files in the variable qtproject_SRCS that require such a file.
# note: this assumes that you use #include "header.moc" in your files
qt4_automoc( ${GLMIXER_UIS_H} ${GLMIXER_SRCS})

# translations
SET(LANG
    "${CMAKE_SOURCE_DIR}/locals/trans_fr.ts"
    "${CMAKE_SOURCE_DIR}/locals/trans_cz.ts"
)
#qt4_create_translation(GLMIXER_QM  ${GLMIXER_UIS_H} ${GLMIXER_SRCS} ${LANG})
qt4_add_translation(GLMIXER_QM ${LANG})


#--------------------------------------------------------------------------------
# For Apple set the icns file containing icons (to do before declaring executable MACOSX_BUNDLE)
IF(APPLE)

  # set how it shows up in the Info.plist file
  SET(MACOSX_BUNDLE_ICON_FILE glmixer.icns)
  # set where in the bundle to put the icns file
  SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/osx/${MACOSX_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  # include the icns file in the target
  SET(GLMIXER_SRCS ${GLMIXER_SRCS} ${CMAKE_SOURCE_DIR}/osx/${MACOSX_BUNDLE_ICON_FILE})

    # create the application
    add_executable(${GLMIXER_BINARY} MACOSX_BUNDLE
            ${GLMIXER_SRCS}
            ${GLMIXER_UIS_H}
            ${GLMIXER_RCS_SRCS}
            ${GLMIXER_QM}
    )


ELSE(APPLE)

    IF(WIN32)

        # This sets up the exe icon for windows under mingw.
        set(RES_FILES "")
        if(MINGW)
            set(RES_FILES "${CMAKE_SOURCE_DIR}/win/glmixer.rc")
            set(CMAKE_RC_COMPILER_INIT windres)
            ENABLE_LANGUAGE(RC)
            SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
        endif(MINGW)

        # create the application
        add_executable(${GLMIXER_BINARY} WIN32
                ${GLMIXER_SRCS}
                ${GLMIXER_UIS_H}
                ${GLMIXER_RCS_SRCS}
                ${GLMIXER_QM}
                ${RES_FILES}
        )



    ELSE(WIN32)

        # create the application
        add_executable(${GLMIXER_BINARY}
                ${GLMIXER_SRCS}
                ${GLMIXER_UIS_H}
                ${GLMIXER_RCS_SRCS}
                ${GLMIXER_QM}
        )



    ENDIF(WIN32)

ENDIF(APPLE)

# link the target against the libraries.
if(USE_NVIDIA_CUDA)
    target_link_libraries(${GLMIXER_BINARY} QtProperty QtColorPicker OSCPack V4l2cpp CUDADecoder ${GLMIXER_LIBRARIES} ${QT_LIBRARIES} ${CUDA_LIBRARIES})
else(USE_NVIDIA_CUDA)
    message(V4l2cpp)
    target_link_libraries(${GLMIXER_BINARY} QtProperty QtColorPicker OSCPack V4l2cpp ${GLMIXER_LIBRARIES} ${QT_LIBRARIES})
endif(USE_NVIDIA_CUDA)


# multiplatform cpack info
SET(CPACK_PACKAGE_NAME "GLMixer")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Graphic Live Mixer\n Real-time video mixing software for live performance.")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
SET(CPACK_PACKAGE_CONTACT "bruno.herbelin@gmail.com")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${GLMIXER_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${GLMIXER_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${GLMIXER_WC_REVISION}")
SET(CPACK_PACKAGE_VENDOR "Bruno Herbelin")
SET(CPACK_SOURCE_IGNORE_FILES "/\\\\.svn/;" )

#--------------------------------------------------------------------------------
# Now the installation stuff below
#--------------------------------------------------------------------------------

IF(APPLE)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/GLMixer.app")
    set(qtplugin_dest_dir GLMixer.app/Contents/MacOS)
    set(qtconf_dest_dir GLMixer.app/Contents/Resources)

    # OSX cpack info
    set( CPACK_SYSTEM_NAME "OSX_${CMAKE_OSX_DEPLOYMENT_TARGET}_${CMAKE_OSX_ARCHITECTURES}")
    set( CPACK_BUNDLE_NAME ${CPACK_PACKAGE_NAME})
    set( CPACK_BUNDLE_PLIST ${CMAKE_SOURCE_DIR}/osx/Info.plist)
    set( CPACK_BUNDLE_ICON ${CMAKE_SOURCE_DIR}/osx/${MACOSX_BUNDLE_ICON_FILE})
    set( CPACK_BINARY_DRAGNDROP ON)

ELSE(APPLE)

    IF(WIN32)
        SET(APPS "\${CMAKE_INSTALL_PREFIX}/${GLMIXER_BINARY}.exe")
        SET(CPACK_PACKAGE_EXECUTABLES "${GLMIXER_BINARY}" "GLMixer")
        SET(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})

        SET(CPACK_GENERATOR "NSIS")
        SET(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/win\\\\glmixer.ico")
        SET(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/win\\\\glmixer.ico")
        SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/win\\\\glmixer.png")
        SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\glmixer.exe")
        SET(CPACK_NSIS_DISPLAY_NAME "GLMixer ${GLMIXER_VERSION_MAJOR}.${GLMIXER_VERSION_MINOR}")
        SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\sourceforge.net\\\\projects\\\\glmixer")
        SET(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_VENDOR} <${CPACK_PACKAGE_CONTACT}>")
        SET(CPACK_NSIS_MODIFY_PATH OFF)
        SET(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL  ON)
        SET(CPACK_NSIS_MUI_FINISHPAGE_RUN "glmixer.exe")
        SET(CPACK_NSIS_HELP_LINK "http://vimeo.com/album/2401475")
        SET(CPACK_NSIS_MENU_LINKS "http://sourceforge.net/projects/glmixer/" "GLMixer Web Site" "plugins" "GLMixer Plugins")

        # SET(CPACK_NSIS_CREATE_ICONS_EXTRA  "
        # CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\scribbleMix.lnk\\\"  \\\"$INSTDIR\\\\bin\\\\scribbleMix.exe\\\"
        # CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\screenMix.lnk\\\"  \\\"$INSTDIR\\\\bin\\\\screenMix.exe\\\"
        # ")
        # SET(CPACK_NSIS_DELETE_ICONS_EXTRA
        # "
        # Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\scribbleMix.lnk\\\"
        # Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\screenMix.lnk\\\"
        # " )

        SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}_${GLMIXER_VERSION_MAJOR}.${GLMIXER_VERSION_MINOR}")

    ELSE(WIN32)
        SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${GLMIXER_BINARY}")
        SET(CPACK_PACKAGE_EXECUTABLES "${GLMIXER_BINARY}" "GLMixer")

        # Linux cpack info
        SET(CPACK_GENERATOR "DEB")
        SET(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
        execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND lsb_release -si OUTPUT_VARIABLE DISTRIBUTION OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND lsb_release -sr OUTPUT_VARIABLE DISTRIB_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)

        if(USE_NVIDIA_CUDA)
        SET(CPACK_SYSTEM_NAME "${DISTRIBUTION}_${DISTRIB_VERSION}_${ARCHITECTURE}_nvidia${NVIDIA_DRIVER_VERSION}")
        else(USE_NVIDIA_CUDA)
        SET(CPACK_SYSTEM_NAME "${DISTRIBUTION}_${DISTRIB_VERSION}_${ARCHITECTURE}")
        endif(USE_NVIDIA_CUDA)

        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR} <${CPACK_PACKAGE_CONTACT}>")
        SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
        SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://sourceforge.net/projects/glmixer/")
        SET(CPACK_DEBIAN_PACKAGE_SECTION "Graphics")
        SET(CPACK_DEBIAN_PACKAGE_VERSION "${GLMIXER_VERSION_MAJOR}.${GLMIXER_VERSION_MINOR}.${GLMIXER_WC_REVISION}")
        SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

        # autogenerate dependency information
        SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        SET(CPACK_STRIP_FILES ON)


    ENDIF(WIN32)
ENDIF(APPLE)


SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${GLMIXER_VERSION_MAJOR}.${GLMIXER_VERSION_MINOR}-${GLMIXER_WC_REVISION}_${CPACK_SYSTEM_NAME}")

#--------------------------------------------------------------------------------
# Install the glmixer application.
# On Apple, the bundle is at the root of the install tree
# On other platforms it'll go into the bin directory.
INSTALL(TARGETS ${GLMIXER_BINARY}
        CONFIGURATIONS Release RelWithDebInfo
        BUNDLE DESTINATION . COMPONENT Runtime
        RUNTIME DESTINATION "./bin" COMPONENT Runtime
    )



IF(APPLE)

    #--------------------------------------------------------------------------------
    # Install needed Qt plugins by copying directories from the qt installation
    # One can cull what gets copied by using 'REGEX "..." EXCLUDE'
    INSTALL(DIRECTORY "${QT_PLUGINS_DIR}/imageformats" DESTINATION ${qtplugin_dest_dir}/plugins COMPONENT Runtime)

    #--------------------------------------------------------------------------------
    # install a qt.conf file
    # this inserts some cmake code into the install script to write the file
    INSTALL(CODE "
        file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"\")
        " COMPONENT Runtime)


    #--------------------------------------------------------------------------------
    # install a qt_menu.nib files structure
    INSTALL(CODE "
        file(MAKE_DIRECTORY \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt_menu.nib\")
        file(COPY \"${QT_LIBRARY_DIR}/QtGui.framework/Versions/4/Resources/qt_menu.nib\" DESTINATION \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}\" NO_SOURCE_PERMISSIONS )
        " COMPONENT Runtime)

    #--------------------------------------------------------------------------------
    # Use BundleUtilities to get all other dependencies for the application to work.
    # It takes a bundle or executable along with possible plugins and inspects it
    # for dependencies.  If they are not system dependencies, they are copied.

    # directories to look for dependencies
    SET(DIRS ${QT_LIBRARY_DIRS} ${CMAKE_LIBRARY_PATH})

    # Now the work of copying dependencies into the bundle/package
    # The quotes are escaped and variables to use at install time have their $ escaped
    # An alternative is the do a configure_file() on a script and use install(SCRIPT  ...).
    # Note that the image plugins depend on QtSvg and QtXml, and it got those copied
    # over.
    INSTALL(CODE "
        file(GLOB_RECURSE QTPLUGINS
          \"\${CMAKE_INSTALL_PREFIX}/${qtplugin_dest_dir}/plugins/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
        " COMPONENT Runtime)

    set(ffplugin_dest_dir GLMixer.app/Contents/MacOS/lib)

    INSTALL(CODE "
        file(GLOB_RECURSE FFPLUGINS
        \"\${CMAKE_INSTALL_PREFIX}/${ffplugin_dest_dir}/*.so\")
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"\${FFPLUGINS}\" \"${DIRS}\")
        " COMPONENT Runtime)

ELSE(APPLE)

  IF(WIN32)

    # uninstall step to remove registry entry
    SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "DeleteRegKey HKCU 'Software\\\\bhbn'")

    # apparently useless, but harmless too..
    INCLUDE(InstallRequiredSystemLibraries)

    # use cmake tools for getting DLL dependencies : I use a custom GetPrerequisites.cmake to support MINGW objdump
    INCLUDE(GetPrerequisites)

    # read full name of executable
    GET_TARGET_PROPERTY(GLMIXER_BINARY_LOCATION ${GLMIXER_BINARY} LOCATION)

    IF( EXISTS ${GLMIXER_BINARY_LOCATION} )

        # call the function get_prerequisites to fill the list DEPENDENCIES
        message( STATUS "Looking for DLL dependencies (please be patient...)" )
        GET_PREREQUISITES(${GLMIXER_BINARY_LOCATION} DEPENDENCIES 1 1 "" "${CMAKE_LIBRARY_PATH}")

        # request the installation of each dll file of the DEPENDENCIES list
        FOREACH(DEPENDENCY ${DEPENDENCIES})
            message(STATUS "  - ${DEPENDENCY}")
            INSTALL(FILES ${DEPENDENCY} DESTINATION bin COMPONENT Runtime)
        ENDFOREACH(DEPENDENCY)

        # IF(MINGW)
            # INSTALL(FILES "/MinGW/bin/mingwm10.dll" DESTINATION bin COMPONENT Runtime)
        # ENDIF(MINGW)

    ELSE( EXISTS ${GLMIXER_BINARY_LOCATION} )

        message( WARNING  "Cannot generate dependency list (DLLs) for packaging because GLMixer was not compiled yet. To enable packaging, re-run cmake after compiling GLMixer." )

    ENDIF( EXISTS ${GLMIXER_BINARY_LOCATION} )

  ELSE(WIN32)

    # Write license file
    file(WRITE "${CMAKE_BINARY_DIR}/copyright"
         "Copyright (C) 2010-2015 ${CPACK_DEBIAN_PACKAGE_MAINTAINER}

       This software may be licensed under the terms of the
       GNU Lesser General Public License Version 3 (the ``LGPL''),
       or (at your option) any later version.

       Software distributed under the License is distributed
       on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
       express or implied. See the LGPL for the specific language
       governing rights and limitations.

       You should have received a copy of the LGPL along with this
       program. If not, go to http://www.gnu.org/licenses/lgpl.html
       or write to the Free Software Foundation, Inc.,
       51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

    On Debian systems, the complete text of the GNU Lesser General Public
    License can be found in `/usr/share/common-licenses/LGPL-3'.")
    install(FILES "${CMAKE_BINARY_DIR}/copyright"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/${GLMIXER_BINARY}/"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
    install(FILES "${CMAKE_SOURCE_DIR}/third-party_attributions"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/${GLMIXER_BINARY}/"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

    # README
    install(FILES "${CMAKE_SOURCE_DIR}/README.txt"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/${GLMIXER_BINARY}/"
            RENAME "README.Debian"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

    # Generate required change log files
    # Use SVN to read repository version
    find_program(XSLTPROC NAMES xsltproc)
    IF(XSLTPROC)
      IF (EXISTS "${CMAKE_SOURCE_DIR}/.svn")
        message( STATUS "Generating ChangeLog from SVN (please be patient...)" )

        execute_process(COMMAND ${CMAKE_SOURCE_DIR}/linux/svn2cl.sh ${CMAKE_SOURCE_DIR}
                        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        execute_process(COMMAND gzip -9 -n -c ${CMAKE_BINARY_DIR}/ChangeLog
                        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                        OUTPUT_FILE "${CMAKE_BINARY_DIR}/changelog.gz")
        install(FILES "${CMAKE_BINARY_DIR}/changelog.gz"
                DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/${GLMIXER_BINARY}/"
                PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
      ENDIF()
    ENDIF()

    # man pages
    execute_process(COMMAND gzip -9 -n -c ${CMAKE_SOURCE_DIR}/linux/glmixer.7
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    OUTPUT_FILE "${CMAKE_BINARY_DIR}/glmixer.7.gz")
    install(FILES "${CMAKE_BINARY_DIR}/glmixer.7.gz"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man7/"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

    # Icon & desktop file
    install(FILES "${CMAKE_SOURCE_DIR}/icons/glmixer.svg"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps/"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
    file(WRITE "${CMAKE_BINARY_DIR}/${GLMIXER_BINARY}.desktop"
       "[Desktop Entry]
        Name=${GLMIXER_BINARY}
        Version=${GLMIXER_VERSION_MAJOR}.${GLMIXER_VERSION_MINOR}
        GenericName=${GLMIXER_BINARY}
        X-GNOME-FullName=${GLMIXER_BINARY}
        Comment=Graphic Live Mixer
        Type=Application
        Categories=${CPACK_DEBIAN_PACKAGE_SECTION}
        Path=${CMAKE_INSTALL_PREFIX}/bin
        Exec=${GLMIXER_BINARY}
        Terminal=false
        StartupNotify=true
        Icon=${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps/glmixer.svg
        TargetEnvironment=Unity
        GenericName[en_ZA]=${GLMIXER_BINARY}")
    install(FILES "${CMAKE_BINARY_DIR}/${GLMIXER_BINARY}.desktop"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications/"
            PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

  ENDIF(WIN32)

ENDIF(APPLE)



# To Create a package, one can run "cpack -G DragNDrop CPackConfig.cmake" on Mac OS X
# where CPackConfig.cmake is created by including CPack
# And then there's ways to customize this as well
include(CPack)
