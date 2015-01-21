#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H
#include <QVector>
#include "puredataosccontroller.h"


class SoundProcessor
{
public:
    SoundProcessor();
    void send(QVector<float> controlData, QVector<QVector<float> > audioData);
    void process(bool sequenzer, int masterVol, QVector< QVector<float> > rawData);
private:
    PureDataOSCController* pureDataOSCController;
private:

   

};

#endif // SOUNDPROCESSOR_H
