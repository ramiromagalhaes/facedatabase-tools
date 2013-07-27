#include <iostream>
#include <string>
#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#define PI 3.14159265358979323846

namespace fs = boost::filesystem;



int main(int argc, char* args[])
{
    if (argc != 3)
    {
        return 1;
    }

    const fs::path sourceFolder( args[1] );
    const fs::path destFolder( args[2] );

    if ( !fs::exists(sourceFolder) || !fs::exists(destFolder) )
    {
        return 2;
    }

    const std::string eyeparams_extension(".eye");

    std::vector<int> pgm_params;
    pgm_params.push_back(CV_IMWRITE_PXM_BINARY);
    pgm_params.push_back(1);


    int resizeCounter = 0;
    fs::directory_iterator end; // default construction == end. Weird...
    for ( fs::directory_iterator it( sourceFolder ); it != end; ++it )
    {
        if ( fs::is_directory(it->status()) || eyeparams_extension.compare(it->path().extension().c_str()) != 0 )
        {
            continue;
        }

        //load eye params
        cv::Point2f rightEye, leftEye;
        {
            fs::ifstream eyeParams;
            eyeParams.open(it->path());
            std::string str;
            std::getline(eyeParams, str);//read useless first line
            int leftEyeX, leftEyeY, rightEyeX, rightEyeY;
            eyeParams >> leftEyeX
                      >> leftEyeY
                      >> rightEyeX
                      >> rightEyeY;

            rightEye.x = rightEyeX;
            rightEye.y = rightEyeY;
            leftEye.x = leftEyeX;
            leftEye.y = leftEyeY;
            eyeParams.close();
        }

        std::string imageFileName = it->path().stem().native() + ".pgm";
        fs::path imagePath = it->path().parent_path() / imageFileName;
        const cv::Mat image = cv::imread(imagePath.native(), CV_8UC1);
        const int len = std::max(image.cols, image.rows);
        if( image.data == 0 )
        {
            std::cerr << "Failed to load file " <<  imagePath.native() << std::endl;
        }

        const float distanceBetweenEyes = cv::norm(rightEye-leftEye);
        const float degreesRotationAroundRightEye = atan((leftEye.y - rightEye.y) / (leftEye.x - rightEye.x)) * 180.0f / PI;

        const float roiWidthHeight = distanceBetweenEyes / 0.5154f;
        const int roiX = rightEye.x - roiWidthHeight * 0.2423f;
        const int roiY = rightEye.y - roiWidthHeight * 0.25f;

        if (roiX < 0 || roiY < 0) {
            std::cerr << "Cannot get ROI from file " <<  imagePath.native() << std::endl;
            std::cerr << roiX <<  " " << roiY << " " << roiWidthHeight << std::endl;
            continue;
        }

        //Now we must scale, rotate and translate the image to have a face ROI.
        const cv::Mat rotMat = cv::getRotationMatrix2D(rightEye, degreesRotationAroundRightEye, 1.0);

        cv::Mat transformed = cv::Mat::zeros(len, len, CV_8UC1);
        cv::warpAffine(image, transformed, rotMat, cv::Size(len, len));

        cv::Rect roi(roiX, roiY, (int)roiWidthHeight, (int)roiWidthHeight);
        cv::Mat face(transformed, roi);

        cv::Mat resizedFace = cv::Mat(20, 20, CV_8UC1);
        cv::resize(face, resizedFace, cv::Size(20, 20)/*, 0, 0, INTER_LINEAR*/);

        const fs::path trainingSamplePath = destFolder / imagePath.filename();
        cv::imwrite(trainingSamplePath.native(), resizedFace);

        resizeCounter++;
    }

    std::cout << "Total images resized: " << resizeCounter << std::endl;

    return 0;
}

