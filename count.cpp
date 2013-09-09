#include <string>
#include <iostream>

#include <OpenImageIO/imageio.h>

namespace oiio = OIIO;



int main(int argc, char* args[])
{
    if (argc != 2)
    {
        return 1;
    }

    const std::string imagePath = args[1]; //"image of images" file path

    oiio::ImageInput *in = oiio::ImageInput::open (imagePath);
    if ( !in )
    {
        return 2;
    }

    const oiio::ImageSpec & spec = in->spec();
    std::cout << spec.width / 20 << std::endl;

    /*
    int channels = spec.nchannels;
    std::vector<unsigned char> pixels ((long)width * heigh * channels);
    in->read_image (oiio::TypeDesc::UINT8, &pixels[0]);
    in->close ();
    */

    delete in;

    return 0;
}
