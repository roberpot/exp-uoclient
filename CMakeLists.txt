CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
PROJECT(uonewclient)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ansi -pedantic -Wextra -std=c++11")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)
FIND_PACKAGE(SDL2_ttf REQUIRED)
FIND_PACKAGE(cashley REQUIRED)

SET(SOURCE_FILES
    common/colorutils.h
    common/debug.cpp
    common/debug.h
    common/errors.h
    common/errors.cpp
    common/textureutils.cpp
    common/textureutils.h
    common/types.h
    common/utils.cpp
    common/utils.h
    engines/video.cpp
    engines/video.h
    resources/gump.cpp
    resources/gump.h
    resources/font.cpp
    resources/font.h
    main.cpp
        common/physicalcomponent.cpp common/physicalcomponent.h common/visualcomponent.cpp common/visualcomponent.h)

add_executable(uonewclient_release ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(uonewclient_release
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${CASHLEY_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
TARGET_COMPILE_DEFINITIONS(uonewclient_release PUBLIC DEBUG_MODE=0)

add_executable(uonewclient_debug ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(uonewclient_debug
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${CASHLEY_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
TARGET_COMPILE_DEFINITIONS (uonewclient_debug PUBLIC DEBUG_MODE=5)