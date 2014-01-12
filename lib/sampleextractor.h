#ifndef SAMPLEEXTRACTOR_H
#define SAMPLEEXTRACTOR_H

#include <string>

#include <opencv2/core/core.hpp>


class SampleExtractor
{
private:
    SampleExtractor();

public:

    /**
     * Randomly 'cuts' samples from a file.
     */
    static bool extractFromBigImage(const unsigned int sample_size,
                                    const std::string & imagePath,
                                    std::vector<cv::Mat> & samples,
                                    std::vector<unsigned int> *sampleIndexes = 0,
                                    cv::Size samplesSize = cv::Size(20,20));

    /**
     * 'Cuts' samples from an image using an index found in a file (indexPath).
     * The index 'points' to rectangles inside the big image. A random index can
     * be obtained from the extractFromBigImage() method that randomly cuts samples
     * from a file.
     */
    static bool extractFromBigImage(const std::string &imagePath,
                                    const std::string &indexPath,
                                    std::vector<cv::Mat> &samples,
                                    cv::Size samplesSize = cv::Size(20,20));

    /**
     * 'Cuts' samples from an image assuming the whole image should be used to
     * extract samples.
     */
    static bool extractFromBigImage(const std::string &imagePath,
                                    std::vector<cv::Mat> &samples,
                                    cv::Size samplesSize = cv::Size(20,20));

    /**
     * The index file contains the paths of images to be loaded.
     */
    static bool extractFromListOfFiles(const std::string &indexPath,
                                       std::vector<cv::Mat> &samples);

};

#endif // SAMPLEEXTRACTOR_H
