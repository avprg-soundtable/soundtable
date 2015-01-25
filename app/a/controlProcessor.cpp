#include "controlProcessor.h"
#include "projectawidget.h"
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
    //Count Frames for Buffer
    frameCount=frameCount+1;
    unprocessedFrameHuge = input;
    //resize for better performance
    resize(unprocessedFrameHuge,unprocessedFrameSmall,Size(640, 480), 0, 0, CV_INTER_AREA);
    //perform preprocessing to highlight objects
    PreProcessedFrame=filterProcessor->preProcess(unprocessedFrameSmall);
    //create binaryimage of objects for further processing
    processedFrame=filterProcessor->process(PreProcessedFrame);
    //set buffer for detecting and sending osc signals
    if (frameCount%2==0){
        rawData = detectProcessor->analyse(processedFrame);
        soundProcessor->process(float(mode),float(masterVol),float(beat) ,rawData);
    }
    //set framecount back to 0 after 2 seconds
    if(frameCount==60){
        frameCount=0;
    }
    //return the binaryimage
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


