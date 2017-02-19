
cmake_minimum_required (VERSION 2.8)
project (LIBFFGLSHAKE)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS -std=gnu++11)
endif()

if(WIN32)
  add_library(ffglShake SHARED FreeFrameShake.cpp)
else(WIN32)
  add_library(ffglShake MODULE FreeFrameShake.cpp)
endif(WIN32)


if(APPLE)
target_link_libraries(ffglShake -Wl,-all_load FreeFrameGL ${OPENGL_LIBRARY})
else(APPLE)
target_link_libraries(ffglShake -Wl,--whole-archive FreeFrameGL -Wl,--no-whole-archive ${OPENGL_LIBRARY})
endif(APPLE)

IF(CMAKE_VERSION VERSION_GREATER 2.9)
    INSTALL(FILES $<TARGET_FILE:ffglShake>
        CONFIGURATIONS Release RelWithDebInfo
        RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )

ELSE()
    get_property(PLUGIN TARGET ffglShake PROPERTY LOCATION)
    INSTALL(FILES ${PLUGIN}
            CONFIGURATIONS Release RelWithDebInfo
            RUNTIME DESTINATION "${FREEFRAME_INSTALL_DIR}" COMPONENT Runtime
    )
ENDIF()
