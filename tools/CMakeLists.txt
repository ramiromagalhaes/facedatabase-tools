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
target_link_libraries( showrand ${OpenCV_LIBS})

#Estimates the variance of samples of a database and returns their indexes sorted from highest to lowest
add_executable( evalsamples "evalsamples.cpp" )
target_link_libraries( evalsamples ${OpenCV_LIBS})
