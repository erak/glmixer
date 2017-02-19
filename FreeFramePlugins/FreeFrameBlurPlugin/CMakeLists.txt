
cmake_minimum_required (VERSION 2.8)
project (LIBFFGLBLUR)

if(WIN32)
  add_library(ffglBlur SHARED FreeFrameBlur.cpp)
else(WIN32)
  add_library(ffglBlur MODULE FreeFrameBlur.cpp)
endif(WIN32)

if(APPLE)
target_link_libraries(ffglBlur -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
else(APPLE)
target_link_libraries(ffglBlur -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
endif(APPLE)

IF(CMAKE_VERSION VERSION_GREATER 2.9)

    INSTALL(FILES $<TARGET_FILE:ffglBlur>
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ELSE()
    get_property(PLUGIN TARGET ffglBlur PROPERTY LOCATION)
    INSTALL(FILES ${PLUGIN}
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ENDIF()
