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
target_link_libraries( showrand ${OpenCV_LIBS})

#Estimates the variance of samples of a database and returns their indexes sorted from highest to lowest
add_executable( evalsamples "evalsamples.cpp" )
target_link_libraries( evalsamples ${OpenCV_LIBS})

