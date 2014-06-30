#include <iostream>
#include <string>
#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace fs = boost::filesystem;



int main(int argc, char* args[])
{
    if (argc != 3)
    {
        return 1;
    }

    const fs::path sourceFolder( args[1] );
    const fs::path destFolder( args[2] );

    if ( !fs::exists(sourceFolder) || !fs::exists(destFolder) )
    {
        return 2;
    }

    std::vector<int> pgm_params;
    pgm_params.push_back(CV_IMWRITE_PXM_BINARY);
    pgm_params.push_back(1);


    const cv::Rect roi(53, 85, 150, 150);

    int resizeCounter = 0;
    fs::directory_iterator end; // default construction == end. Weird...
    for ( fs::directory_iterator it( sourceFolder ); it != end; ++it )
    {
        if ( fs::is_directory(it->status()) )
        {
            continue;
        }

        const cv::Mat image = cv::imread(it->path().native(), CV_8UC1);
        if( image.data == 0 )
        {
            std::cerr << "Failed to load file " <<  it->path().native() << std::endl;
        }

        cv::Mat face(image, roi);

        cv::Mat resizedFace = cv::Mat(20, 20, CV_8UC1);
        cv::resize(face, resizedFace, cv::Size(20, 20)/*, 0, 0, INTER_LINEAR*/);

        const fs::path trainingSamplePath = destFolder / (it->path().stem().native() + ".pgm");
        cv::imwrite(trainingSamplePath.native(), resizedFace);

        resizeCounter++;
    }

    std::cout << "Total images resized: " << resizeCounter << std::endl;

    return 0;
}
