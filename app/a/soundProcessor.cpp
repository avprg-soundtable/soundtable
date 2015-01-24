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


void SoundProcessor::process(float sequenzer, float masterVol,float seqSpeed, QVector< QVector<float> > rawData){
    QVector<float> rawObject;
    QVector<float> audioObject(15);
    controlData.clear();
    audioData.clear();
    controlData.append(masterVol);
    if (sequenzer==1){
        controlData.append(0); //create off
        controlData.append(1);  //sequenzer on
    }else{
        controlData.append(1); //create off
        controlData.append(0);  //sequenzer on
    }
    controlData.append(float(rawData.size()));
    controlData.append(seqSpeed);
    int numberParams = 15;    //number of parameters
    int numberInsertedAudioObjects =0;
    for(int i = 0; i < rawData.size(); i++){                    //Anzahl gefundener Objekte
       //qDebug() << "Arraygroesse Raw Data: " << rawData.size();
        if (rawData.isEmpty()==false){                            //
            if (rawData[i].isEmpty()==false){
                rawObject=rawData[i];
                if(rawObject.isEmpty()==false){
                    audioObject.append(calcSawOn(rawObject));                           //Flag if audio object exists
                    audioObject.append(calcSawNote(rawObject));                //x coordinate
                    audioObject.append(calcSawVolume(rawObject));                //y coordinate
                    audioObject.append(calcSawHarmon(rawObject));
                    audioObject.append(calcSinOn(rawObject));
                    audioObject.append(calcSinNote(rawObject));
                    audioObject.append(calcSinVolume(rawObject));
                    audioObject.append(calcSinModul(rawObject));
                    audioObject.append(calcSinHarmon(rawObject));
                    audioObject.append(calcSquareOn(rawObject));
                    audioObject.append(calcSquareNote(rawObject));
                    audioObject.append(calcSquareVolume(rawObject));
                    audioObject.append(calcSquareModul(rawObject));
                    audioObject.append(calcSquareHarmon(rawObject));
                 }
             }
        }
        audioData.append(audioObject);
        numberInsertedAudioObjects=numberInsertedAudioObjects+1;
    }
    for(int k = 0; k < 15-numberInsertedAudioObjects; k++)            //Fülle restlichen audioObjekte mit 0
     {
                for(int j = 0; j < numberParams; j++){
                    audioObject[j]=0;
                }
                audioData.append(audioObject);
     }
        //qDebug() << "Arraygroesse controlDATA: " << controlData.size();
        send(controlData,audioData);
}

float SoundProcessor::calcSawOn(QVector<float> rawObject){
    if (rawObject[5]>=15){
        return 1;
    }else{
        return 0;
    }
}
float SoundProcessor::calcSawNote(QVector<float> rawObject){
   qDebug() << "Groesse " << rawObject[3];
    float note=rawObject[3];
    int min = 64;
    int max = 15064;
    if(note<=min){
        note=min;
    }
    if(note>=max){
        note= max;
    }
    note=note-min;
    note=note/max;
//    note=((note)*(note)*(3-2*(note)));
//    note=((note)*(note)*(3-2*(note)));
//    note=((note)*(note)*(3-2*(note)));
    note=1-note;
    note=note*89+1;
    int rounded = note;
    qDebug() << "Note " << rounded;
    return float(rounded);
}
float SoundProcessor::calcSawVolume(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSawModul(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSawHarmon(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSinOn(QVector<float> rawObject){
    if (rawObject[5]>=18){
        return 0;
    }else{
        return 1;
    }
}
float SoundProcessor::calcSinNote(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSinVolume(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSinModul(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSinHarmon(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSquareOn(QVector<float> rawObject){
    if ((rawObject[5]>=8)&&(rawObject[5]<=16)){
        return 1;
    }else{
        return 0;
    }
}
float SoundProcessor::calcSquareNote(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSquareVolume(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSquareModul(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSquareHarmon(QVector<float> rawObject){
    return 1;
}
void SoundProcessor::send(QVector<float> controlData, QVector< QVector<float> > audioData){
     //qDebug() << "AudioData " << audioData.size();
     pureDataOSCController->sendOSC("/masterVol",controlData[0]);
     pureDataOSCController->sendOSC("/create",controlData[1]);
     pureDataOSCController->sendOSC("/sequenz",controlData[2]);
     pureDataOSCController->sendOSC("/objCount",controlData[3]);
     pureDataOSCController->sendOSC("/seqSpeed",controlData[4]);
//     qDebug() << "Control Vol: " << controlData[0];
//     qDebug() << "Control create: " << controlData[1];
//     qDebug() << "Control sequenz " << controlData[2];
//     qDebug() << "Control ObjCount: " << controlData[3];
//     qDebug() << "Control seqSpeed: " << controlData[4];

     QVector<float> audioObject;
     for(int i = 0; i < audioData.size(); i++){
         audioObject=audioData[i];
         QString route=("/object") + QString::number( i+1 );
             pureDataOSCController->sendOSC(route+"/sawOn",audioObject[0]);
             pureDataOSCController->sendOSC(route+"/sawNote",audioObject[1]);
             pureDataOSCController->sendOSC(route+"/sawVolume",audioObject[2]);
             pureDataOSCController->sendOSC(route+"/sawModul",audioObject[3]);
             pureDataOSCController->sendOSC(route+"/sawHarmon",audioObject[4]);
             pureDataOSCController->sendOSC(route+"/sinOn",audioObject[5]);
             pureDataOSCController->sendOSC(route+"/sinNote",audioObject[6]);
             pureDataOSCController->sendOSC(route+"/sinVolume",audioObject[7]);
             pureDataOSCController->sendOSC(route+"/sinModul",audioObject[8]);
             pureDataOSCController->sendOSC(route+"/sinHarmon",audioObject[9]);
             pureDataOSCController->sendOSC(route+"/squareOn",audioObject[10]);
             pureDataOSCController->sendOSC(route+"/squareNote",audioObject[11]);
             pureDataOSCController->sendOSC(route+"/squareVolume",audioObject[12]);
             pureDataOSCController->sendOSC(route+"/squareModul",audioObject[13]);
             pureDataOSCController->sendOSC(route+"/squareHarmon",audioObject[14]);
         }

     }





