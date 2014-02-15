#include <iostream>
#include <string>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



struct entry {
    unsigned int index;
    double stdDev;

    bool operator < (const entry & e) const
    {
        return stdDev > e.stdDev;
    }
};



/**
 * Evaluates image samples. Receives as argument the path of the image that
 * is a composition of 20x20 samples of images. Outputs indexes of samples ordered
 * by decreasing variance.
 */
int main(int argc, char* args[])
{
    if (argc < 2 && argc > 3)
    {
        return 3;
    }
    const std::string imagePath = args[1];

    { //image exists?
        std::ifstream in(imagePath.c_str());
        if ( !in.is_open() )
        {
            return 2;
        }
        in.close();
    }

    const cv::Size roiSize(20 ,20);
    const cv::Mat full_image = cv::imread(imagePath, cv::DataType<unsigned char>::type);

    std::vector<entry> stdDeviations;

    for (int i = 0; i < full_image.cols; i += roiSize.width)
    {
        const cv::Rect sampleRoi(i, 0, roiSize.width, roiSize.height);
        const cv::Mat sample = full_image(sampleRoi);

        cv::Scalar mean;
        cv::Scalar stdDev;

        cv::meanStdDev(sample, mean, stdDev);

        entry e;
        e.index = i / roiSize.width;
        e.stdDev = stdDev[0];

        stdDeviations.push_back(e);
    }

    std::sort(stdDeviations.begin(), stdDeviations.end());

    for(std::vector<entry>::iterator it = stdDeviations.begin(); it - stdDeviations.begin() < 6000; ++it)
    {
        std::cout << it->index << ' ';
    }
    std::cout << std::endl;

    return 0;
}
