#include "soundProcessor.h"
#include <QDebug>

#include "videoprocessor.h"

using namespace cv;


SoundProcessor::SoundProcessor():
    pureDataOSCController(new PureDataOSCController)
{


}

void SoundProcessor::process(bool sequenzer, int masterVol, QVector< QVector<float> > rawData){

    //check if raw changes are over threshold
    //convert raw into Audio
    //fill all audioData array fields



}

void SoundProcessor::send(QVector<float> controlData, QVector< QVector<float> > audioData){
    if (audioData.isEmpty()==false){
        if (audioData.first().isEmpty()==false){
            //pureDataOSCController->sendOSC();
        }

    }

}




