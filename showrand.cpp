#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <cmath>
#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/unordered_set.hpp>


bool extractRandomSample(const unsigned int sample_size,
                         const std::string &imagePath,
                         std::vector<cv::Mat> &samples,
                         std::vector<unsigned int > *sampleIndexes = 0)
{
    boost::unordered_set<unsigned int> selectedIndexes;

    std::srand(std::time(0));

    const cv::Size roiSize(20 ,20);
    const cv::Mat full_image = cv::imread(imagePath, cv::DataType<unsigned char>::type);


    for (unsigned int i = 0; i < sample_size; ++i)
    {
        unsigned int sampleX = 0;
        bool did_insert = false;
        do
        {
            sampleX = (full_image.cols/roiSize.width) * ((float)std::rand() / RAND_MAX);
            did_insert = selectedIndexes.insert(sampleX).second;
        } while ( !did_insert );

        if (sampleIndexes)
        {
            sampleIndexes->push_back(sampleX);
        }

        cv::Rect roi(sampleX * 20, 0, roiSize.width, roiSize.height);

        cv::Mat image = cv::Mat(full_image, roi);
        if ( !image.data )
        {
            return false;
        }

        samples.push_back(image);
    }

    return true;
}



int main(int argc, char* args[])
{
    const std::string imagePath = args[1];
    const int samplesToExtract = 400;

    { //image exists?
        std::ifstream in(imagePath.c_str());
        if ( !in.is_open() )
        {
            return 2;
        }
        in.close();
    }

    std::vector<cv::Mat> samples;

    extractRandomSample(samplesToExtract, imagePath, samples);

    cv::Mat output = cv::Mat::zeros(20 * (samplesToExtract / 100 + (samplesToExtract % 100 != 0)),
                                    2000,
                                    cv::DataType<unsigned char>::type);

    for (unsigned int i = 0; i < samples.size(); ++i)
    {
        cv::Rect output_roi( (i * 20) % output.cols,
                              20 * (i * 20 / output.cols),
                              20, 20 );

        samples[i].copyTo(output(output_roi));
    }

    cv::imshow("Selected ROI", output);
    cv::waitKey(0);

    return 0;
}
