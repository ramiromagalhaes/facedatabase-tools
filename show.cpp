#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char* args[])
{
    if (argc < 3)
    {
        return 1;
    }
    const std::string filePath = args[1];
    int index;
    {
        std::stringstream ss;
        ss << args[2];
        ss >> index;
    }

    { //file exists?
        std::ifstream in(filePath.c_str());
        if ( !in.is_open() )
        {
            return 2;
        }
        in.close();
    }

    cv::Mat image = cv::imread(filePath, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Rect roi(index * 20, 0, 1000, 20);

    cv::imshow("Selected ROI", image(roi));
    cv::waitKey(0);

    return 0;
}
