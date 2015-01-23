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
    cv::Mat preProcess(const Mat &input);
    void setMedianEnable(bool enable);
    void setOpeningEnable(bool enable);
    void setAlpha(double pAlpha);
    void setBeta(int pBeta);
    void setfTau(double pfTau);
    void setUseEqualization(bool enable);
    void setUseBufferMode(bool enable);
    void setUseNoiseReduction(bool enable);
    void setSigmaBackground(int pSigma);
    void setBufferSize(int pBufferSize);
    void reinitializeBG(Mat& background);
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
    bool useNoiseRecution;
    bool bufferMode;
    double alpha;
    int beta;
    int bufferSize;
    double fTau;
    int sigmaBackground;
    cv::Mat bufferFrame;
    int frameCount;
    Ptr<BackgroundSubtractor> pMOG2;

};

#endif // COLORKEYERHSV_H
