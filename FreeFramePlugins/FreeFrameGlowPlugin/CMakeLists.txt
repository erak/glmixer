cmake_minimum_required (VERSION 2.8)
project (LIBFFGLGLOW)

if(WIN32)
  add_library(ffglGlow SHARED FreeFrameGlow.cpp)
else(WIN32)
  add_library(ffglGlow MODULE FreeFrameGlow.cpp)
endif(WIN32)

if(APPLE)
target_link_libraries(ffglGlow -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
else(APPLE)
target_link_libraries(ffglGlow -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
endif(APPLE)

IF(CMAKE_VERSION VERSION_GREATER 2.9)
    INSTALL(FILES $<TARGET_FILE:ffglGlow>
        CONFIGURATIONS Release RelWithDebInfo
        RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ELSE()
    get_property(PLUGIN TARGET ffglGlow PROPERTY LOCATION)
    INSTALL(FILES ${PLUGIN}
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ENDIF()
