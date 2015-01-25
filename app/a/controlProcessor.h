#ifndef CONTROLPROCESSOR_H
#define CONTROLPROCESSOR_H
#include <QImage>
#include "videoprocessor.h"
#include "filterProcessor.h"
#include "detectProcessor.h"
#include "soundProcessor.h"
using namespace cv;


class ControlProcessor : public VideoProcessor
{
public:
    ControlProcessor();
    ~ControlProcessor();
    void startProcessing(const VideoFormat& format){}
    cv::Mat process(const cv::Mat&source);
    int sendtestvalue;
    void setMasterVol(float vol);
    void setBeat(float pBeat);
    void setMode(float pMode);
    void setMute(float pMute);
    FilterProcessor* filterProcessor;
    DetectProcessor* detectProcessor;
    cv::Mat unprocessedFrameHuge;
    cv::Mat unprocessedFrameSmall;
signals:
    void sendPreProcessedImage(const QImage&);


private:

    SoundProcessor* soundProcessor;
    float masterVol;
    float beat;
    float mode;
    float mute;


    int frameCount;

    cv::Mat PreProcessedFrame;
    cv::Mat processedFrame;
    QVector< QVector<float> > rawData;



};

#endif // CONTROLLPROCESSOR_H
