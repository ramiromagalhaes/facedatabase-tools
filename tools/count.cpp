#include <string>
#include <iostream>

#include <OpenImageIO/imageio.h>

namespace oiio = OIIO;



/**
 * Counts the amount of samples a database has.
 * A sample database is just an image where each sample is placed side-by-side.
 * It is assumed that each sample is a 20x20 pixels image.
 */
int main(int argc, char* args[])
{
    int sample_size = 20;

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
    std::cout << spec.width / sample_size << std::endl;

    delete in;

    return 0;
}
