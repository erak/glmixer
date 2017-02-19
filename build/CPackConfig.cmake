# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_PRODUCTBUILD "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_BUILD_SOURCE_DIRS "/home/bitshift/Dev/cpp/glmixer;/home/bitshift/Dev/cpp/glmixer/build")
SET(CPACK_CMAKE_GENERATOR "Ninja")
SET(CPACK_COMPONENTS_ALL "Runtime;Unspecified")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Graphic Live Mixer
 Real-time video mixing software for live performance.")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://sourceforge.net/projects/glmixer/")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Bruno Herbelin <bruno.herbelin@gmail.com>")
SET(CPACK_DEBIAN_PACKAGE_NAME "GLMixer")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "Graphics")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS "ON")
SET(CPACK_DEBIAN_PACKAGE_VERSION "1.5.")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/home/bitshift/Dev/cpp/glmixer/build;glmixer;ALL;/")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/home/bitshift/Dev/cpp/glmixer")
SET(CPACK_NSIS_DISPLAY_NAME "GLMixer 1.5.")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "GLMixer 1.5.")
SET(CPACK_OUTPUT_CONFIG_FILE "/home/bitshift/Dev/cpp/glmixer/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "bruno.herbelin@gmail.com")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/home/bitshift/Dev/cpp/glmixer/README.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Graphic Live Mixer
 Real-time video mixing software for live performance.")
SET(CPACK_PACKAGE_EXECUTABLES "glmixer;GLMixer")
SET(CPACK_PACKAGE_FILE_NAME "GLMixer_1.5-___amd64")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "GLMixer 1.5.")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "GLMixer 1.5.")
SET(CPACK_PACKAGE_NAME "GLMixer")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Bruno Herbelin")
SET(CPACK_PACKAGE_VERSION "1.5.")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "5")
SET(CPACK_PACKAGE_VERSION_PATCH "")
SET(CPACK_RESOURCE_FILE_LICENSE "/home/bitshift/Dev/cpp/glmixer/COPYING.txt")
SET(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.7/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.7/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "/\\.svn/;")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/bitshift/Dev/cpp/glmixer/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_RPM "OFF")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TXZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_STRIP_FILES "ON")
SET(CPACK_SYSTEM_NAME "__amd64")
SET(CPACK_TOPLEVEL_TAG "__amd64")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/bitshift/Dev/cpp/glmixer/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()