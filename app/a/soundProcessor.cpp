#include "soundProcessor.h"
#include <QDebug>

#include "videoprocessor.h"

using namespace cv;


SoundProcessor::SoundProcessor():
    pureDataOSCController(new PureDataOSCController)
{

}

SoundProcessor::~SoundProcessor()
{
    //delete pureDataOSCController;
}


void SoundProcessor::process(bool sequenzer, int masterVol, QVector< QVector<float> > rawData){

    QVector<float> rawObject;
    QVector<float> audioObject(4);
    controlData.clear();
    audioData.clear();
    controlData.append(sequenzer);
    controlData.append(masterVol);
    int numberParams = 4;    //number of parameters
    for(int i = 0; i < rawData.size(); i++){
       qDebug() << "Arraygroesse: " << rawData.size();
        if (rawData.isEmpty()==false){
            if (rawData[i].isEmpty()==false){
                rawObject=rawData[i];
                if(rawObject.isEmpty()==false){
                    audioObject.append(1);                           //Flag if audio object exists
                    audioObject.append(rawObject[1]);                //x coordinate
                    audioObject.append(rawObject[2]);                //y coordinate
                    audioObject.append(calcFrequency(rawObject));    //frequency
                 }
             }
        }else{
            //fill array with 0's
            for(int j = 0; j < numberParams; j++){
                audioObject[j]=0;
            }
        }

        audioData.append(audioObject);

    }

        send(controlData,audioData);

}

float SoundProcessor::calcFrequency(QVector<float> rawObject){
    float area=rawObject[3];
    if (area<64){
        area=64;
    }
    if (area>12000){
        area=12000;
    }
    return -1,5*area+18096;
}

void SoundProcessor::send(QVector<float> controlData, QVector< QVector<float> > audioData){
     qDebug() << "AudioData " << audioData.size();
     pureDataOSCController->sendOSC("/control",controlData[0]);
     pureDataOSCController->sendOSC("/control2",controlData[1]);
     QVector<float> audioObject;
     for(int i = 0; i < audioData.size(); i++){
         audioObject=audioData[i];
         QString route=("/object") + QString::number( i );

             pureDataOSCController->sendOSC(route+"/frequency",audioObject[3]);
         }

     }





