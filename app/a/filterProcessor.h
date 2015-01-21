#ifndef FILTERPROCESSOR_H
#define FILTERPROCESSOR_H

#include "videoprocessor.h"
using namespace cv;
using namespace std;

class FilterProcessor : public VideoProcessor
{
public:
    FilterProcessor();
    ~FilterProcessor();
    void startProcessing(const VideoFormat& format){}
    cv::Mat process(const cv::Mat&source);
    void setMedianEnable(bool enable);
    void setOpeningEnable(bool enable);
    void reinitializeBG(cv::Mat& background);
private:
    cv::Mat filter(cv::Mat& input);
    cv::Mat equalization(Mat& frame);
    cv::Mat noiseRecution(cv::Mat& binaryMask);
    cv::Mat removeShadows(Mat& frame);
private:
    cv::Point center;
    bool useMedian;
    bool useOpening;
    bool useEqualization;
    bool useNoiseRecutiob;
    bool bufferMode;
    cv::Mat bufferFrame;
    int frameCount;
    Ptr<BackgroundSubtractor> pMOG2;

};

#endif // COLORKEYERHSV_H
