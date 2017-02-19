
cmake_minimum_required (VERSION 2.8)
project (LIBQTCOLORPICKER)


include(${QT_USE_FILE})

set(LIBQTCOLORPICKER_SRCS
	qtcolorpicker.cpp
)


# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories (${LIBQTCOLORPICKER_SOURCE_DIR}) 

# tell cmake to create .moc files for all files in the variable qtproject_SRCS that require such a file.
# note: this assumes that you use #include "header.moc" in your files
qt4_automoc( ${LIBQTCOLORPICKER_SRCS} )

add_library (QtColorPicker ${LIBQTCOLORPICKER_SRCS})  