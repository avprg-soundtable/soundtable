#ifndef CONTROLPROCESSOR_H
#define CONTROLPROCESSOR_H

#include "videoprocessor.h"
#include "filterProcessor.h"
#include "detectProcessor.h"
#include "soundProcessor.h"
using namespace cv;

class ControlProcessor : public VideoProcessor
{
public:
    ControlProcessor();
    void startProcessing(const VideoFormat& format){}
    cv::Mat process(const cv::Mat&source);
    int sendtestvalue;
    
private:
    FilterProcessor* filterProcessor;
    DetectProcessor* detectProcessor;
    SoundProcessor* soundProcessor;

    int frameCount;
    cv::Mat unprocessedFrame;
    cv::Mat processedFrame;
    QVector< QVector<float> > rawData;



};

#endif // CONTROLLPROCESSOR_H
