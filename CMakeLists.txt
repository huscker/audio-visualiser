cmake_minimum_required(VERSION 3.10)

project(AudioVisualiser LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

add_executable(AudioVisualiser main.cpp)
target_link_libraries(AudioVisualiser ImageGen)
target_link_libraries(AudioVisualiser FractalGen)
target_link_libraries(AudioVisualiser AudioHandler)
target_link_libraries(AudioVisualiser m pthread)
#target_link_libraries(RayMarching GL glut GLEW glfw)