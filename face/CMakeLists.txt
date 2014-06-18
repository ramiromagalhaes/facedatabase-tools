#To manipulate the MIT-CBCL database
add_executable( cbcl "cbcl.cpp" )
target_link_libraries( cbcl ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To manipulate the BioID database
add_executable( bioid "bioid.cpp" )
target_link_libraries( bioid ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To manipulate the FEI database
add_executable( fei "fei.cpp" )
target_link_libraries( fei ${OpenCV_LIBS} ${Boost_LIBRARIES} )

#To manipulate the AR database
add_executable( ar "ar.cpp" )
target_link_libraries( ar ${OpenCV_LIBS} ${Boost_LIBRARIES} )

