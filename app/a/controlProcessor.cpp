#include "controlProcessor.h"
#include <QDebug>
#include <QImage>
#include "../libs/videoengine/cvmattoqimage.h"
using namespace cv;


ControlProcessor::ControlProcessor():
    filterProcessor(new FilterProcessor())
  , detectProcessor(new DetectProcessor())
  , soundProcessor(new SoundProcessor())
  , frameCount(0)
  , sendtestvalue(0)
  , rawData(15)
  , masterVol(2)
  , mode(0)
  , beat(350)
{

}

ControlProcessor::~ControlProcessor()
{
    delete filterProcessor;
    delete detectProcessor;
    delete soundProcessor;
}
Mat ControlProcessor::process(const Mat &input){
    frameCount=frameCount+1;
    unprocessedFrameHuge = input;
    resize(unprocessedFrameHuge,unprocessedFrameSmall,Size(640, 480), 0, 0, CV_INTER_AREA);
    PreProcessedFrame=filterProcessor->preProcess(unprocessedFrameSmall);
    //emit sendPreProcessedImage(cvMatToQImage(PreProcessedFrame));
    processedFrame=filterProcessor->process(PreProcessedFrame);
    if (frameCount%3==0){
        rawData = detectProcessor->analyse(processedFrame);
        soundProcessor->process(float(mode),float(masterVol),float(beat) ,rawData);
    }
    if(frameCount==60){
        frameCount=0;
    }
    return processedFrame;

}
void ControlProcessor::setMute(float pMute){
    mute=pMute;
}

void ControlProcessor::setMasterVol(float vol){
    masterVol=vol;
}
void ControlProcessor::setMode(float pMode){
    mode=pMode;
}
void ControlProcessor::setBeat(float pBeat){
    beat=pBeat;
}


