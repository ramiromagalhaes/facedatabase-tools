#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define SHOW_USAGE std::cout << "Usage: " << args[0] << " IMAGE_PATH INDEX_PATH";


/**
 * Shows samples listed in the second argument taken from the first argument.
 */
int main(int argc, char* args[])
{
    if (argc != 3)
    {
        std::cout << SHOW_USAGE;
    }

    const std::string imagePath = args[1];
    const std::string indexPath = args[2];

    std::vector<int> indexes;
    {
        std::ifstream in(indexPath.c_str());
        if ( !in.is_open() )
        {
            return 1;
        }

        while(true)
        {
            int index;
            in >> index;

            if ( in.eof() )
            {
                break;
            }

            indexes.push_back(index);
        }

        in.close();
    }

    { //source image exists?
        std::ifstream in(imagePath.c_str());
        if ( !in.is_open() )
        {
            return 2;
        }
        in.close();
    }

    cv::Mat image = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);

    cv::Mat output = cv::Mat::zeros(20 * (indexes.size() / 100 + (indexes.size() % 100 != 0)),
                                    2000,
                                    cv::DataType<unsigned char>::type);

    for (unsigned int i = 0; i < indexes.size(); ++i)
    {
        cv::Rect input_roi(indexes[i] * 20, 0, 20, 20);

        cv::Rect output_roi( (i * 20) % output.cols,
                              20 * (i * 20 / output.cols),
                              20, 20 );

        image(input_roi).copyTo(output(output_roi));
    }

    cv::imshow("Selected ROI", output);
    cv::waitKey(0);

    return 0;
}
