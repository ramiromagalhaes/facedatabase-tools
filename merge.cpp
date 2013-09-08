#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



int main(int argc, char* args[])
{
    if (argc != 3)
    {
        return 1;
    }

    const boost::filesystem::path indexFile = args[1];
    const boost::filesystem::path outputFolder = args[2];

    if ( !boost::filesystem::exists(indexFile)
         || !boost::filesystem::is_regular_file(indexFile)
         || !boost::filesystem::exists(outputFolder)
         || !boost::filesystem::is_directory(outputFolder) )
    {
        return 2;
    }

    boost::filesystem::ifstream index(indexFile);



    const int totalImages = std::count(std::istreambuf_iterator<char>(index),
                                       std::istreambuf_iterator<char>(), '\n');
    index.clear();
    index.seekg(0, std::ios::beg);

    std::cout << "Total of images found on index: " << totalImages << std::endl;

    const int maxImagesPerFile = std::numeric_limits<int>::max() / 20;
    const int totalFiles = 1 + totalImages / maxImagesPerFile;

    int totalImagesProcessed = 0;

    for (int currentFile = 0; currentFile < totalFiles; ++currentFile)
    {
        const int imagesInThisFile =
            totalImages - totalImagesProcessed > maxImagesPerFile ?
                    maxImagesPerFile : totalImages - totalImagesProcessed;

        cv::Mat output(20, 20 * imagesInThisFile, CV_8U);

        for(int i = 0; i < imagesInThisFile; ++i)
        {
            std::string imagePathString;
            std::getline(index, imagePathString);

            if ( index.eof() )
            {
                break;
            }

            const cv::Mat img = cv::imread(imagePathString, cv::IMREAD_GRAYSCALE);
            if (img.data == 0)
            {
                return 1000;
            }

            const cv::Rect roi_rect(20 * i, 0, 20, 20);
            cv::Mat roi (output, roi_rect);
            img.copyTo(roi);
        }

        totalImagesProcessed += imagesInThisFile;

        std::stringstream fileNumber;
        fileNumber << currentFile << ".pgm";
        boost::filesystem::path outputPath = outputFolder / fileNumber.str();
        std::cout << "Writing file " << outputPath.native() << "." << std::endl;
        cv::imwrite(outputPath.native(), output);
    }

    return 0;
}
