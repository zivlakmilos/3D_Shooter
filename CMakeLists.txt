project(mersuthepig)

cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(SOURCES
    src/main.cpp
)

INCLUDE_DIRECTORIES(include/)
INCLUDE_DIRECTORIES(libs/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(${PROJECT_NAME} ${SOURCES})

INCLUDE_DIRECTORIES(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)
