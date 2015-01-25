#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H
#include <QVector>
#include "puredataosccontroller.h"


class SoundProcessor
{
public:
    SoundProcessor();
    ~SoundProcessor();
    void send(QVector<float> controlData, QVector<QVector<float> > audioData);
    void process(float sequenzer, float masterVol,float seqSpeed, QVector< QVector<float> > rawData);
private:
    PureDataOSCController* pureDataOSCController;
    QVector< QVector<float> > audioData;
    QVector< QVector<float> > audioDataBuffer;
    QVector< float > controlData;
    QVector< float > controlDataBuffer;
    float calcSawOn(QVector<float> rawObject);
    float calcSawNote(QVector<float> rawObject);
    float calcSawVolume(QVector<float> rawObject);
    float calcSawModul(QVector<float> rawObject);
    float calcSawHarmon(QVector<float> rawObject);
    float calcSinOn(QVector<float> rawObject);
    float calcSinNote(QVector<float> rawObject);
    float calcSinVolume(QVector<float> rawObject);
    float calcSinModul(QVector<float> rawObject);
    float calcSinHarmon(QVector<float> rawObject);
    float calcSquareOn(QVector<float> rawObject);
    float calcSquareNote(QVector<float> rawObject);
    float calcSquareVolume(QVector<float> rawObject);
    float calcSquareModul(QVector<float> rawObject);
    float calcSquareHarmon(QVector<float> rawObject);
    float calcSimpleFmOn(QVector<float> rawObject);
    float calcSimpleFmNote(QVector<float> rawObject);
    float calcSimpleFmVolume(QVector<float> rawObject);
    float calcSimpleFmModul(QVector<float> rawObject);
private:

   

};

#endif // SOUNDPROCESSOR_H
