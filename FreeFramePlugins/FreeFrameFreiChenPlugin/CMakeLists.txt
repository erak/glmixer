cmake_minimum_required (VERSION 2.8)
project (LIBFFGLFREICHEN)

if(WIN32)
  add_library(ffglFreiChen SHARED FreeFrameFreiChen.cpp)
else(WIN32)
  add_library(ffglFreiChen MODULE FreeFrameFreiChen.cpp)
endif(WIN32)

if(APPLE)
target_link_libraries(ffglFreiChen -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
else(APPLE)
target_link_libraries(ffglFreiChen -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
endif(APPLE)

IF(CMAKE_VERSION VERSION_GREATER 2.9)
    INSTALL(FILES $<TARGET_FILE:ffglFreiChen>
        CONFIGURATIONS Release RelWithDebInfo
        RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ELSE()
    get_property(PLUGIN TARGET ffglFreiChen PROPERTY LOCATION)
    INSTALL(FILES ${PLUGIN}
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ENDIF()
