cmake_minimum_required(VERSION 2.8)

project(trainingdatabase-tools)

# Debug and release configurations
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -D_DEBUG -Wextra -Wall")
set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# This is where all binaries should be placed
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

# Using OIIO 1.3.2
set(OIIO_DIST_DIR /home/ramiro/workspace/oiio/dist/linux64/)
include_directories(${OIIO_DIST_DIR}/include)
link_directories(${OIIO_DIST_DIR}/lib)

# More on find_package command http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
find_package( OpenCV REQUIRED COMPONENTS core imgproc highgui )
find_package( Boost  REQUIRED COMPONENTS filesystem system )

# The library...
add_subdirectory(lib)

# ...and the tools
add_subdirectory(tools)
