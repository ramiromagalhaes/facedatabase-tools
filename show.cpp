#include <iostream>
#include <string>
#include <sstream>

#include <OpenImageIO/imageio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

OIIO_NAMESPACE_USING

#define BUFF_SIZE 400

int main(int argc, char* args[])
{
    if (argc != 3)
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

    ImageInput *in = ImageInput::open (filePath);
    const ImageSpec & spec = in->spec();
    const imagesize_t size = (imagesize_t)spec.width * spec.height; //Notice one of the rvalues must be of type
                                                                    //imagesize_t, or the result will be coerced to int
                                                                    //and be a lot smaller than needed
    unsigned char * pixels = new unsigned char[size];
    in->read_image(TypeDesc::UCHAR, pixels);
    in->close();
    std::cout << "Done reading." << std::endl;

    cv::Mat image(spec.height, spec.width, CV_8UC1, pixels);
    cv::Rect roi(index * 20, 0, 20, 20);

    cv::imshow("Selected ROI", image(roi));
    cv::waitKey(0);

    return 0;
}
