
cmake_minimum_required (VERSION 2.6)
project (LIBESCAPIFFGL)

include_directories(${FREEFRAMEGL_DIR_PLUGINS})

set(LIBESCAPIFFGL_SRCS
    escapi.cpp
    escapiFFGL.cpp
)

#find_library(PTHREAD_LIBRARY pthread REQUIRED)

add_library(escapiffgl MODULE ${LIBESCAPIFFGL_SRCS} )

target_link_libraries(escapiffgl -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY}  ${GLEW_LIBRARY} )

INSTALL(FILES "escapi.dll"
    CONFIGURATIONS Release RelWithDebInfo
    RUNTIME DESTINATION "./bin" COMPONENT Runtime
)
