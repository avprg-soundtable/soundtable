#include "controlProcessor.h"
#include <QDebug>
using namespace cv;


ControlProcessor::ControlProcessor():
    filterProcessor(new FilterProcessor())
  , detectProcessor(new DetectProcessor())
  , soundProcessor(new SoundProcessor())
  , frameCount(0)
  , sendtestvalue(0)
  , rawData(15)
{

}

Mat ControlProcessor::process(const Mat &input){
    frameCount=frameCount+1;
    unprocessedFrame = input;
    processedFrame=filterProcessor->process(unprocessedFrame);
    rawData = detectProcessor->analyse(processedFrame);
    soundProcessor->send(rawData);

    return processedFrame;
    
   }



