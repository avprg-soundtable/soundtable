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
    int countCorners(Mat& image);
    void centerOfMass(cv::Mat& image);
private:
    QVector< QVector<float> > sortRawData(QVector< QVector<float> > rawData);

private:


};

#endif // DetectPROCESSOR_H
