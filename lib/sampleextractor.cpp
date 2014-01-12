#include "sampleextractor.h"

#include <fstream>
#include <cmath>
#include <ctime>
#include <utility>
#include <opencv2/highgui/highgui.hpp>
#include <boost/unordered_set.hpp>



SampleExtractor::SampleExtractor() {}



//TODO ensure that the same sample won't be chosen again.
bool SampleExtractor::extractFromBigImage(const unsigned int sample_size,
                                          const std::string &imagePath,
                                          std::vector<cv::Mat> &samples,
                                          std::vector<unsigned int > *sampleIndexes,
                                          cv::Size samplesSize)
{
    boost::unordered_set<unsigned int> selectedIndexes; //know them so we do not pick tem again

    std::srand(std::time(0));

    const cv::Mat full_image = cv::imread(imagePath, cv::DataType<unsigned char>::type);


    for (unsigned int i = 0; i < sample_size; ++i)
    {
        unsigned int sampleX = 0;
        bool did_insert = false;
        do
        {
            sampleX = (full_image.cols/samplesSize.width) * ((float)std::rand() / RAND_MAX);
            did_insert = selectedIndexes.insert(sampleX).second;
        } while ( !did_insert );

        if (sampleIndexes)
        {
            sampleIndexes->push_back(sampleX);
        }

        cv::Rect roi(sampleX * 20, 0, samplesSize.width, samplesSize.height);

        cv::Mat image = cv::Mat(full_image, roi);
        if ( !image.data )
        {
            return false;
        }

        samples.push_back(image);
    }

    return true;
}

bool SampleExtractor::extractFromBigImage(const std::string &imagePath,
                                          const std::string &indexPath,
                                          std::vector<cv::Mat> &samples,
                                          cv::Size samplesSize)
{
    std::ifstream indexStream(indexPath.c_str());
    if (!indexStream.is_open())
    {
        return false;
    }

    const cv::Mat full_image = cv::imread(imagePath, cv::DataType<unsigned char>::type);
    if (full_image.data == 0)
    {
        return false;
    }

    while(! indexStream.eof() )
    {
        std::string line;
        std::getline(indexStream, line);

        if (line.empty())
        {
            break;
        }

        std::istringstream lineInputStream(line);
        int index;
        lineInputStream >> index;

        const cv::Rect sampleRoi(index * samplesSize.width, 0, samplesSize.width, samplesSize.height);
        const cv::Mat sample = full_image(sampleRoi);

        samples.push_back(sample);
    }

    return true;
}

bool SampleExtractor::extractFromBigImage(const std::string &imagePath,
                                          std::vector<cv::Mat> &samples,
                                          cv::Size samplesSize)
{
    const cv::Mat full_image = cv::imread(imagePath, cv::DataType<unsigned char>::type);

    unsigned int total_images = full_image.cols / samplesSize.width;
    samples.resize(total_images);
    for (unsigned int i = 0; i < total_images; ++i)
    {
        cv::Rect roi(i * 20, 0, samplesSize.width, samplesSize.height);

        cv::Mat image = cv::Mat(full_image, roi);
        if ( !image.data )
        {
            return false;
        }

        samples[i] = image;
    }

    return true;
}

bool SampleExtractor::extractFromListOfFiles(const std::string & indexPath, std::vector<cv::Mat> &samples)
{
    std::ifstream indexStream(indexPath.c_str());
    if (!indexStream.is_open())
    {
        return false;
    }

    while( !indexStream.eof() )
    {
        std::string imagePath;
        std::getline(indexStream, imagePath);

        if (imagePath.empty())
        {
            break;
        }

        //TODO check if all image sizes comply with some parameter, like size
        cv::Mat image = cv::imread(imagePath, cv::DataType<unsigned char>::type);
        if ( !image.data )
        {
            return false;
        }

        samples.push_back(image);
    }

    indexStream.close();

    return true;
}
