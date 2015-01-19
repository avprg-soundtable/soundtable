#ifndef DETECTPROCESSOR_H
#define DETECTPROCESSOR_H

#include "videoprocessor.h"
using namespace cv;

class DetectProcessor
{
public:
    DetectProcessor();
    QVector< QVector<float> > analyse(const cv::Mat&source); //Rueckgabe anpassen!
    QVector<float> RegionAnalyse(const cv::Mat &input);
    void centerOfMass(cv::Mat& image);
private:

private:


};

#endif // DetectPROCESSOR_H
