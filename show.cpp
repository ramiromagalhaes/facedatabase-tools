#include <iostream>
#include <string>
#include <OpenImageIO/imagecache.h>

namespace oiio = OpenImageIO::v1_2;


int main(int argc, char* args[])
{
    /*
    if (argc != 2)
    {
        return 1;
    }
    */

    const std::string imagesDirectory = "/home/ramiro/Imagens/"; //args[1];



    // Create an image cache and set some options
    oiio::ImageCache *cache = oiio::ImageCache::create();
    cache->attribute("max_memory_MB", 40000); //40GB
    cache->attribute("searchpath", imagesDirectory);

    std::string filePath = "0.pgm";

    oiio::ImageSpec spec;
    bool ok = cache->get_imagespec(oiio::ustring(filePath), spec); //not able to use std::string???
    if ( !ok )
    {
        return 2;
    }


    unsigned char pixels[400]; //width * height * channels of the samples = 20*20*1

    int i = 0;
    for(int x = 0; x < spec.width; x += 20, i++)
    {
        cache->get_pixels (oiio::ustring(filePath),
                       0, 0,
                       x, x + 20,
                       0, 20,
                       0, 0,
                       oiio::TypeDesc::UCHAR,
                       pixels);
    }

    oiio::ImageCache::destroy(cache);

    std::cout << i;

    return 0;
}
