# ...

set(source_files sampleextractor.h
                 sampleextractor.cpp)
add_library( trainingdatabase-lib SHARED ${source_files} )
target_link_libraries( trainingdatabase-lib ${OpenCV_LIBS} )
