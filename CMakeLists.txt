project(3dshoter)

cmake_minimum_required(VERSION 2.8)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Project source code
set(SOURCES
    src/engine/core/pngimage.cpp
    
    src/engine/errors/zexception.cpp
    src/engine/errors/zoutofrangeexception.cpp
    src/engine/errors/debug.cpp
    
    src/engine/render/renderer.cpp
    src/engine/render/shader.cpp
    src/engine/render/vertexarray.cpp
    src/engine/render/texture.cpp
    src/engine/render/camera.cpp
    
    src/engine/zapplication.cpp
    src/engine/zwindow.cpp
)

# Inlucde directories for libraries
set(INCLUDE_DIRS
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
)

# Libraries for linking
set(LIBRARIES
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_STATIC_LIBRARIES}
    ${PNG_LIBRARIES}
)

# Configuration
include_directories(${INCLUDE_DIRS})
include_directories(include/)
include_directories(3rdparty/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Compiling
add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

# Linking
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Google unit test (optional)
find_package(GTest)
if(${GTEST_FOUND})
    set(TEST_SOURECES
        test/vect2_test.cpp
        test/vect3_test.cpp
        test/matrix_transform_2d.cpp
    )

    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(test test/main.cpp ${TEST_SOURECES} ${SOURCES})
    target_link_libraries(test ${GTEST_LIBRARIES} ${LIBRARIES})
endif()
