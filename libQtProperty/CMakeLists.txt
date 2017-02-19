
cmake_minimum_required (VERSION 2.8)
project (LIBQTPROPERTY)


include(${QT_USE_FILE})

set(LIBQTPROPERTY_SRCS
	qtbuttonpropertybrowser.cpp  
	qtgroupboxpropertybrowser.cpp  
	qtpropertybrowserutils.cpp  
	qttreepropertybrowser.cpp
	qteditorfactory.cpp          
	qtpropertybrowser.cpp          
	qtpropertymanager.cpp       
	qtvariantproperty.cpp
)

set(LIBQTPROPERTY_RCS
   qtpropertybrowser.qrc
)


# do the qt-cmake magic
qt4_add_resources(LIBQTPROPERTY_RCS_SRCS ${LIBQTPROPERTY_RCS})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories (${LIBQTPROPERTY_SOURCE_DIR}) 

include_directories(${QT_QTOPENGL_INCLUDE_DIR} ${QT_QTXML_INCLUDE_DIR})

# tell cmake to create .moc files for all files in the variable qtproject_SRCS that require such a file.
# note: this assumes that you use #include "header.moc" in your files
qt4_automoc( ${LIBQTPROPERTY_SRCS} )

add_library (QtProperty ${LIBQTPROPERTY_SRCS} ${LIBQTPROPERTY_RCS_SRCS})  