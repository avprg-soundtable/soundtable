#include "soundProcessor.h"
#include <QDebug>

#include "videoprocessor.h"

using namespace cv;


SoundProcessor::SoundProcessor():
    pureDataOSCController(new PureDataOSCController)
 
{
    qDebug() << "OSC Test ";

}

void SoundProcessor::send(QVector< QVector<float> > rawData){
    qDebug() << "OSC send ";
    qDebug() << "Arraysize " << rawData.size();
    if (rawData.isEmpty()==false){
        qDebug() << "Array...: " ;
        if (rawData.first().isEmpty()==false){
            pureDataOSCController->sendOSC(rawData.first().first());
        }

    }

}




