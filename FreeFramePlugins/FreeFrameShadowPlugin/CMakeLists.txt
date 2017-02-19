
cmake_minimum_required (VERSION 2.6)
project (LIBFFGLSHADOW)

if(WIN32)
  add_library(ffglShadow SHARED FreeFrameShadow.cpp)
else(WIN32)
  add_library(ffglShadow MODULE FreeFrameShadow.cpp)
endif(WIN32)

if(APPLE)
target_link_libraries(ffglShadow -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY})
else(APPLE)
target_link_libraries(ffglShadow -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY})
endif(APPLE)

IF(CMAKE_VERSION VERSION_GREATER 2.9)
    INSTALL(FILES $<TARGET_FILE:ffglShadow>
        CONFIGURATIONS Release RelWithDebInfo
        RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )

ELSE()
    get_property(PLUGIN TARGET ffglShadow PROPERTY LOCATION)
    INSTALL(FILES ${PLUGIN}
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ENDIF()
