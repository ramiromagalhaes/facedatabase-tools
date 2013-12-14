cmake_minimum_required(VERSION 2.8)

project(facedatabase-tools)

# Debug and release configurations
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -D_DEBUG -Wextra -Wall")
set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

include_directories(/home/ramiro/workspace/oiio/dist/linux64.debug/include)
link_directories(/home/ramiro/workspace/oiio/dist/linux64.debug/lib)

# More on find_package command http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
find_package( OpenCV REQUIRED COMPONENTS core imgproc highgui )
find_package( Boost 1.54.0 REQUIRED COMPONENTS filesystem system )

#To manipulate the MIT-CBCL database
add_executable( cbcl "cbcl.cpp" )
target_link_libraries( cbcl ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To manipulate the BioID database
add_executable( bioid "bioid.cpp" )
target_link_libraries( bioid ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To manipulate the FEI database
add_executable( fei "fei.cpp" )
target_link_libraries( fei ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To manipulate the FEI database
add_executable( ar "ar.cpp" )
target_link_libraries( ar ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To merge samples in one big file
add_executable( merge "merge.cpp" )
target_link_libraries( merge ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To merge samples in one big file
add_executable( count "count.cpp" )
target_link_libraries( count OpenImageIO)

#Display samples from a list of indexes
add_executable( show "show.cpp" )
target_link_libraries( show ${OpenCV_LIBS} OpenImageIO)

#Display samples randomly
add_executable( showrand "showrand.cpp" )
target_link_libraries( showrand ${OpenCV_LIBS} OpenImageIO)
