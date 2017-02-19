
cmake_minimum_required (VERSION 2.8)
project (LIBFFGLWAVE)

if(WIN32)
  add_library(ffglWave SHARED FreeFrameWave.cpp)
else(WIN32)
  add_library(ffglWave MODULE FreeFrameWave.cpp)
endif(WIN32)

if(APPLE)
target_link_libraries(ffglWave -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY})
else(APPLE)
target_link_libraries(ffglWave -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY})
endif(APPLE)

IF(CMAKE_VERSION VERSION_GREATER 2.9)
    INSTALL(FILES $<TARGET_FILE:ffglWave>
        CONFIGURATIONS Release RelWithDebInfo
        RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ELSE()
    get_property(PLUGIN TARGET ffglWave PROPERTY LOCATION)
    INSTALL(FILES ${PLUGIN}
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ENDIF()
