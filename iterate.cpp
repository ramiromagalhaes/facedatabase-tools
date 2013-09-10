#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>

#include <OpenImageIO/imagebuf.h>
#include <opencv2/core/core.hpp>

OIIO_NAMESPACE_USING

#define BUFF_SIZE 400

int main(int argc, char* args[])
{
    if (argc != 2)
    {
        return 1;
    }

    char const * const indexPath = args[1];

    std::ifstream indexStream(indexPath);
    if (!indexStream.is_open())
    {
        return 2;
    }

    ImageCache *cache = ImageCache::create();
    cache->attribute ("max_memory_MB", 40000.0); //40GB
    //TODO try to set the directory

    std::vector<std::string> imagesPaths;
    while( !indexStream.eof() )
    {
        std::string imagePathString;
        std::getline(indexStream, imagePathString);

        if (imagePathString.empty())
        {
            break;
        }

        imagesPaths.push_back(imagePathString);
        ImageBuf buffer(imagePathString, cache); //insert a buffer in a cache.
    }

    unsigned char pixels[400];

    for( std::vector<std::string>::const_iterator it = imagesPaths.begin(); it != imagesPaths.end(); ++it )
    {
        ImageSpec spec;
        if (! cache->get_imagespec( ustring(*it), spec) )
        {
            //TODO Throw exception?
            std::cerr << "Failed to get metadata about " << *it << '\n';
            continue;
        }

        for (int x = 0; x < spec.width; x+=20)
        {
            cache->get_pixels( ustring(*it),              //the file
                               0, 0,                      //subimage and texture or whatever
                               x, x + 20, 0, 20,          //x and y
                               0, 1, 0, 1,                //z and channels
                               TypeDesc::UCHAR, pixels ); //the data
        }
    }

    ImageCache::destroy(cache);
    return 0;
}
