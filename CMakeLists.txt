CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(uonewclient)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)
FIND_PACKAGE(SDL2_ttf REQUIRED)
FIND_PACKAGE(cashley REQUIRED)

SET(SOURCE_FILES
    common/colorutils.h
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
        common/errors.h common/errors.cpp)

add_executable(uonewclient ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(uonewclient
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${CASHLEY_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
