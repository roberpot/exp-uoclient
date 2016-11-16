CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
PROJECT(uonewclient)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ansi -pedantic -Wextra -std=c++11")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)
FIND_PACKAGE(SDL2_ttf REQUIRED)
FIND_PACKAGE(cashley REQUIRED)

IF(CMAKE_COMPILER_IS_GNUCC)
    FIND_PACKAGE(GLEW REQUIRED)
ENDIF(CMAKE_COMPILER_IS_GNUCC)

SET(ARTIFACTS_SOURCE_FILES
        artifacts/gumps/basegump.cpp
        artifacts/gumps/basegump.h
        artifacts/gumps/button.cpp
        artifacts/gumps/button.h
        artifacts/gumps/gumppic.cpp
        artifacts/gumps/gumppic.h
        artifacts/gumps/gumps.h
        artifacts/gumps/passwordentry.cpp
        artifacts/gumps/passwordentry.h
        artifacts/gumps/resizepic.cpp
        artifacts/gumps/resizepic.h
        artifacts/gumps/text.cpp
        artifacts/gumps/text.h
        artifacts/gumps/textentry.cpp
        artifacts/gumps/textentry.h
        artifacts/artifact.cpp
        artifacts/artifact.h
        artifacts/form.cpp
        artifacts/form.h
        artifacts/inputreader.cpp
        artifacts/inputreader.h
        )

SET(CASHLEY_SOURCE_FILES
        cashley/inputprocessor.cpp
        cashley/inputprocessor.h
        cashley/physicalcomponent.cpp
        cashley/physicalcomponent.h
        cashley/physicsprocessor.cpp
        cashley/physicsprocessor.h
        cashley/visualcomponent.cpp
        cashley/visualcomponent.h
        cashley/visualprocessor.cpp
        cashley/visualprocessor.h
        )

SET(COMMON_SOURCE_FILES
        common/garbagecollector/displaylist.cpp
        common/garbagecollector/displaylist.h
        common/garbagecollector/resourcereferencer.cpp
        common/garbagecollector/resourcereferencer.h
        common/garbagecollector/texture.cpp
        common/garbagecollector/texture.h
        common/colorutils.cpp
        common/colorutils.h
        common/core.cpp
        common/core.h
        common/debug.cpp
        common/debug.h
        common/errors.h
        common/errors.cpp
        common/key.cpp
        common/key.h
        common/textureutils.cpp
        common/textureutils.h
        common/types.h
        common/utils.cpp
        common/utils.h
        )

SET(CONTRIB_SOURCE_FILES
        contrib/form_login.cpp
        contrib/form_login.h
        )

SET(ENGINES_SOURCE_FILES
        engines/input.cpp
        engines/input.h
        engines/video.cpp
        engines/video.h
        )

SET(RESOURCES_SOURCE_FILES
        resources/entry3d.h
        resources/font.cpp
        resources/font.h
        resources/gump.cpp
        resources/gump.h
        resources/hues.cpp
        resources/hues.h
        resources/indexfile.cpp
        resources/indexfile.h
        )

SET(SHADERS_SOURCE_FILES
        shaders/textureloader.cpp
        shaders/textureloader.h
        )

SET(SOURCE_FILES
        ${ARTIFACTS_SOURCE_FILES}
        ${CASHLEY_SOURCE_FILES}
        ${COMMON_SOURCE_FILES}
        ${CONTRIB_SOURCE_FILES}
        ${ENGINES_SOURCE_FILES}
        ${RESOURCES_SOURCE_FILES}
        ${SHADERS_SOURCE_FILES}
        main.cpp)

add_executable(uonewclient_release ${SOURCE_FILES})
add_executable(uonewclient_info ${SOURCE_FILES})
add_executable(uonewclient_msg ${SOURCE_FILES})

IF(CMAKE_COMPILER_IS_GNUCC)
    TARGET_LINK_LIBRARIES(uonewclient_release
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${CASHLEY_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(uonewclient_info
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${CASHLEY_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(uonewclient_msg
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${CASHLEY_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
    )
ELSE(CMAKE_COMPILER_IS_GNUCC)
    TARGET_LINK_LIBRARIES(uonewclient_release
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${CASHLEY_LIBRARY}
        ${OPENGL_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(uonewclient_info
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${CASHLEY_LIBRARY}
        ${OPENGL_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(uonewclient_msg
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${CASHLEY_LIBRARY}
        ${OPENGL_LIBRARIES}
    )
ENDIF(CMAKE_COMPILER_IS_GNUCC)

TARGET_COMPILE_DEFINITIONS(uonewclient_release PUBLIC DEBUG_MODE=0)
TARGET_COMPILE_DEFINITIONS(uonewclient_info PUBLIC DEBUG_MODE=4)
TARGET_COMPILE_DEFINITIONS(uonewclient_msg PUBLIC DEBUG_MODE=5)