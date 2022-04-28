# CMake file for OpenGL Projects using GLUT
# Cross platform as long as OpenGL and GLUT libraries/includes are in the right places

cmake_minimum_required(VERSION 3.16)
project(GraphicsGroupProject)

# CMake vars
set(CMAKE_CXX_STANDARD 20)

# CLion's default cmake profiles put all the cmakefiles in a cmake-build-<profile name> dir
# move the build dirs one level out from that dir if that is the case
if($ENV{CLION_IDE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ../bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
    set(LIBRARY_OUTPUT_PATH ../lib)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
    set(LIBRARY_OUTPUT_PATH lib)
endif()

# Project vars
add_subdirectory(src/vector)
set(SOURCE_FILES src/main.cpp src/Part1.cpp src/Part2.cpp src/globals.cpp)

# OpenGL vars
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

# Executable creation and linking
add_executable(GraphicsGroupProject ${SOURCE_FILES})
target_link_libraries(GraphicsGroupProject OpenGL::GL OpenGL::GLU GLUT::GLUT vector)
target_compile_features(GraphicsGroupProject PRIVATE cxx_std_20)

# Copy the dynamic libraries to binary folder after build
if(WIN32) # FreeGLUT is packaged as a stub .lib plus a .DLL
  add_custom_command (TARGET GraphicsGroupProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_LIST_DIR}/lib"
      $<TARGET_FILE_DIR:GraphicsGroupProject>)
endif()
