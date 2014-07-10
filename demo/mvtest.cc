#include <iostream>
#include "libmv-capi.h"
#include <opencv2/opencv.hpp>
// #include <opencv2/core/utility.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
	libmv_DetectOptions options = {0};
    libmv_Features *features = NULL;
    Mat im = imread("./haderner/haderner1.jpg", 1);
    Mat im_resized;
    int feat_num = 0;
    namedWindow("haderner", 1);
    resize(im, im_resized, Size(im.cols>>2, im.rows>>2));
    std::cout << "w: " << im_resized.cols << "h: " << im_resized.rows << std::endl;
	options.detector = LIBMV_DETECTOR_HARRIS;
    options.margin = 2;
    options.min_distance = 50;
    options.harris_threshold = 1e-5;
    features = libmv_detectFeaturesByte(im_resized.data, im_resized.cols,
                             im_resized.rows  , 3, &options);
    feat_num = libmv_countFeatures(features);
    std::cout << "features num: " << feat_num << endl;
    for (int i = 0; i < feat_num; ++i)
    {
        double x, y, score, size;
        libmv_getFeature(features, i, &x, &y, &score, &size);
        circle(im_resized, Point(x, y), 4, CV_RGB(0,255,0));
    }
    
    for (; ; )
    {
        imshow("haderner", im_resized);
        int key = waitKey(10);
        if (key == 27)
        {
            break;
        }
    }
    libmv_featuresDestroy(features);
    return 0;
}
