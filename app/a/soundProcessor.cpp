#include "soundProcessor.h"
#include <QDebug>
#include "videoprocessor.h"

using namespace cv;

SoundProcessor::SoundProcessor():
    pureDataOSCController(new PureDataOSCController)
{
    for(int i = 0; i < 5; i++){
        controlDataBuffer.append(9999); //create first controlldatabuffer that should be overwritten by sending first signals
    }
    for(int n = 0; n < 15; n++){    //create first controlldatabuffer that should be overwritten by sending first signals
        QVector<float> audioObjectBuffer(15);
        for(int m = 0; m < 15; m++){
            audioObjectBuffer.append(9999);
         }
        audioDataBuffer.append(audioObjectBuffer);
    }

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
        audioObject.clear();
        if (rawData.isEmpty()==false){                            //
            if (rawData[i].isEmpty()==false){
                rawObject=rawData[i];
                if(rawObject.isEmpty()==false){
                    audioObject.append(calcSawOn(rawObject));                           //Flag if audio object exists
                    audioObject.append(calcSawNote(rawObject));                //x coordinate
                    audioObject.append(calcSawVolume(rawObject));
                    audioObject.append(calcSawModul(rawObject));
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
                audioObject.clear();
                for(int j = 0; j < numberParams; j++){
                    audioObject.append(0);
                }
                audioData.append(audioObject);
     }
        send(controlData,audioData);
}
float SoundProcessor::calcSawOn(QVector<float> rawObject){
    if (rawObject[5]<=12){
        return 1;
    }else{
        return 0;
    }
}
float SoundProcessor::calcSawNote(QVector<float> rawObject){
    float note=rawObject[3];
    int min = 64;
    int max = 10064;
    if(note<=min){
        note=min;
    }
    if(note>=max){
        note= max;
    }
    note=note-min;
    note=note/max;
    note=((note)*(note)*(3-2*(note)));
//  note=((note)*(note)*(3-2*(note)));
//  note=((note)*(note)*(3-2*(note)));
    note=1-note;
    note=note*89+1;
    int rounded = note;
    return float(rounded);
}
float SoundProcessor::calcSawVolume(QVector<float> rawObject){
    float vol;
    int min = 0;
    int max = 480;
    vol=rawObject[2];
    vol=vol-min;
    vol=vol/max;
    vol=((vol)*(vol)*(3-2*(vol)));
    vol=vol*5;
    return vol;
}
float SoundProcessor::calcSawModul(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSawHarmon(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSinOn(QVector<float> rawObject){
    if (rawObject[5]>=10){
        return 0;
    }else{
        return 1;
    }
}
float SoundProcessor::calcSinNote(QVector<float> rawObject){
    float note=rawObject[3];
    int min = 64;
    int max = 10064;
    if(note<=min){
        note=min;
    }
    if(note>=max){
        note= max;
    }
    note=note-min;
    note=note/max;
    note=((note)*(note)*(3-2*(note)));
//  note=((note)*(note)*(3-2*(note)));
//  note=((note)*(note)*(3-2*(note)));
    note=1-note;
    note=note*89+1;
    int rounded = note;
    return float(rounded);
}
float SoundProcessor::calcSinVolume(QVector<float> rawObject){
    float vol;
    int min = 0;
    int max = 480;
    vol=rawObject[2];
    vol=vol-min;
    vol=vol/max;
    vol=((vol)*(vol)*(3-2*(vol)));
    vol=vol*5;
    return vol;
}
float SoundProcessor::calcSinModul(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSinHarmon(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSquareOn(QVector<float> rawObject){
    if ((rawObject[5]>=8)&&(rawObject[5]<=15)){
        return 1;
    }else{
        return 0;
    }
}
float SoundProcessor::calcSquareNote(QVector<float> rawObject){
    float note=rawObject[3];
    int min = 64;
    int max = 10064;
    if(note<=min){
        note=min;
    }
    if(note>=max){
        note= max;
    }
    note=note-min;
    note=note/max;
    note=((note)*(note)*(3-2*(note)));
//  note=((note)*(note)*(3-2*(note)));
//  note=((note)*(note)*(3-2*(note)));
    note=1-note;
    note=note*89+1;
    int rounded = note;
    return float(rounded);
}
float SoundProcessor::calcSquareVolume(QVector<float> rawObject){
    float vol;
    int min = 0;
    int max = 480;
    vol=rawObject[2];
    vol=vol-min;
    vol=vol/max;
    vol=((vol)*(vol)*(3-2*(vol)));
    vol=vol*5;
    return vol;
}
float SoundProcessor::calcSquareModul(QVector<float> rawObject){
    return 1;
}
float SoundProcessor::calcSquareHarmon(QVector<float> rawObject){
    return 1;
}
void SoundProcessor::send(QVector<float> controlData, QVector< QVector<float> > audioData){
    if (controlDataBuffer[0]!=controlData[0]){
     pureDataOSCController->sendOSC("/masterVol",controlData[0]);
    }
    if (controlDataBuffer[1]!=controlData[1]){
     pureDataOSCController->sendOSC("/create",controlData[1]);
    }
    if (controlDataBuffer[2]!=controlData[2]){
     pureDataOSCController->sendOSC("/sequenz",controlData[2]);
    }
    if (controlDataBuffer[3]!=controlData[3]){
     pureDataOSCController->sendOSC("/objCount",controlData[3]);
    }
    if (controlDataBuffer[4]!=controlData[4]){
     pureDataOSCController->sendOSC("/seqSpeed",controlData[4]);
    }

     QVector<float> audioObject;
     QVector<float> audioObjectBuffer;
     for(int i = 0; i < audioData.size(); i++){
         audioObject=audioData[i];
         audioObjectBuffer=audioDataBuffer[i];
         QString route=("/object") + QString::number( i+1 );
         if (audioObject[0]!=audioObjectBuffer[0]){
             pureDataOSCController->sendOSC(route+"/sawOn",audioObject[0]);
         }
         if (audioObject[1]!=audioObjectBuffer[1]){
             pureDataOSCController->sendOSC(route+"/sawNote",audioObject[1]);
         }
             if (audioObject[2]!=audioObjectBuffer[2]){
             pureDataOSCController->sendOSC(route+"/sawVolume",audioObject[2]);
         }
             if (audioObject[3]!=audioObjectBuffer[3]){
             pureDataOSCController->sendOSC(route+"/sawModul",audioObject[3]);
         }
             if (audioObject[4]!=audioObjectBuffer[4]){
             pureDataOSCController->sendOSC(route+"/sawHarmon",audioObject[4]);
         }
             if (audioObject[5]!=audioObjectBuffer[5]){
             pureDataOSCController->sendOSC(route+"/sinOn",audioObject[5]);
         }
             if (audioObject[6]!=audioObjectBuffer[6]){
             pureDataOSCController->sendOSC(route+"/sinNote",audioObject[6]);
         }
             if (audioObject[7]!=audioObjectBuffer[7]){
             pureDataOSCController->sendOSC(route+"/sinVolume",audioObject[7]);
         }
             if (audioObject[8]!=audioObjectBuffer[8]){
             pureDataOSCController->sendOSC(route+"/sinModul",audioObject[8]);
         }
             if (audioObject[9]!=audioObjectBuffer[9]){
             pureDataOSCController->sendOSC(route+"/sinHarmon",audioObject[9]);
         }
             if (audioObject[10]!=audioObjectBuffer[10]){
             pureDataOSCController->sendOSC(route+"/squareOn",audioObject[10]);
         }
             if (audioObject[11]!=audioObjectBuffer[11]){
             pureDataOSCController->sendOSC(route+"/squareNote",audioObject[11]);
         }
             if (audioObject[12]!=audioObjectBuffer[12]){
             pureDataOSCController->sendOSC(route+"/squareVolume",audioObject[12]);
         }
             if (audioObject[13]!=audioObjectBuffer[13]){
             pureDataOSCController->sendOSC(route+"/squareModul",audioObject[13]);
         }
             if (audioObject[14]!=audioObjectBuffer[14]){
             pureDataOSCController->sendOSC(route+"/squareHarmon",audioObject[14]);
            }
         }
     controlDataBuffer=controlData;
     audioDataBuffer=audioData;
}





