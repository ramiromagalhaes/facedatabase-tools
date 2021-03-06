#include <iostream>

#include <boost/filesystem.hpp>
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


    int resizeCounter = 0;
    fs::directory_iterator end; // default construction == end. Weird...
    for ( fs::directory_iterator it( sourceFolder ); it != end; ++it )
    {
        if ( fs::is_directory(it->status()) )
        {
            continue;
        }

        //resize image
        const cv::Mat image = cv::imread(it->path().native(), CV_8UC1);
        cv::Mat resized = cv::Mat(20, 20, CV_8UC1);
        cv::resize(image, resized, cv::Size(20, 20)/*, 0, 0, INTER_LINEAR*/);

        fs::path destFile = destFolder / it->path().filename();
        cv::imwrite(destFile.native(), resized, pgm_params);

        resizeCounter++;
    }

    std::cout << "Total images resized: " << resizeCounter << std::endl;

    return 0;
}

