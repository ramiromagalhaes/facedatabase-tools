# ...

set(lib_files sampleextractor.h
              sampleextractor.cpp)
add_library( trainingdatabase-lib SHARED ${lib_files} )
target_link_libraries( trainingdatabase-lib ${OpenCV_LIBS} )
