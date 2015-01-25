#include "detectProcessor.h"
#include <QVector>
#include <QDebug>
using namespace cv;

DetectProcessor::DetectProcessor()
{

}
DetectProcessor::~DetectProcessor()
{

}
QVector< QVector<float> > DetectProcessor::analyse(const Mat &input){
    Mat mask;
    QVector< QVector<float> > datas(15);
    input.copyTo(mask);
    vector<vector<Point> >contours;
    findContours(mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    int anzahlGefundenerObjekte = contours.size();
    if (anzahlGefundenerObjekte>=14)
    {
        anzahlGefundenerObjekte=14;
    }
    for(int i = 0; i < anzahlGefundenerObjekte; i++)
    {
        Mat maskSingleRegion(mask.rows,mask.cols,CV_8UC1,Scalar(0, 0, 0));
        drawContours(maskSingleRegion, contours, i, Scalar(255, 255, 255), CV_FILLED);
        datas[i]=RegionAnalyse(maskSingleRegion);

    }
    datas=sortRawData(datas);
    for(int n = 0; n < datas.size(); n++)
    {
        if (datas[n].isEmpty()==false)
        {
            for(int m = 0; m < datas[n].size(); m++)
            {

            }
        }
    }
    return datas;
}

QVector< QVector<float> > DetectProcessor::sortRawData(QVector< QVector<float> > rawData){

    QVector< QVector<float> > copyOfRawData = rawData;
    QVector< QVector<float> > sortedRawData;
    if (rawData.isEmpty()==false){

        for(int i = 0; i < rawData.size(); i++){
            int maxX = 0;
            int maxXIndex = 0;

            for(int j = 0; j < copyOfRawData.size(); j++){
                if (copyOfRawData[j].isEmpty()==false){
                int x = copyOfRawData[j][1];
                  if (maxX < x ){
                        maxX = x;
                        maxXIndex = j;
                    }
                }
            }
            if (maxX!=0){
                sortedRawData.append(copyOfRawData[maxXIndex]);
                copyOfRawData.removeAt(maxXIndex);
            }
        }
        return sortedRawData;
   }else{
        return rawData;
    }

}

QVector<float> DetectProcessor::RegionAnalyse(const Mat &input){
    Mat maskSingleRegion;
    Mat copyOfMask;
    QVector<float> regionRaw(12);
    input.copyTo(maskSingleRegion);
    maskSingleRegion.copyTo(copyOfMask);
    vector<vector<Point> >contours;
    findContours(copyOfMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    vector<Point>contour = contours[0];
    //vectors for approxed polygon
    vector<vector<Point> >approxContours(1);
    vector<Point> approxContour;
    //approx the shape
    approxPolyDP(contour,approxContour,0.05*arcLength(contour,true),true);
    approxContours[0]=approxContour;
    //create mat with approxed Shape for corner detection
    Mat maskSingleRegionApproxed(maskSingleRegion.rows,maskSingleRegion.cols,CV_8UC1,Scalar(0, 0, 0));
    drawContours(maskSingleRegionApproxed, approxContours, 0, Scalar(255, 255, 255), CV_FILLED);
    Moments imageMoments = moments(contour);
    CvRect boundingMaskRect = boundingRect(contour);
    RotatedRect minBoundingMaskRect = minAreaRect(contour);
    RotatedRect boundingEllipseMask = fitEllipse(contour);
    // Flag ob Objekt existiert
    regionRaw[0]= 1;
    // X Koordinaten
    regionRaw[1]= imageMoments.m10/imageMoments.m00;
    // Y Koordinaten
    regionRaw[2]= imageMoments.m01/imageMoments.m00;
    // Area
    regionRaw[3]= imageMoments.m00;
    // Umfang
    regionRaw[4]= arcLength(approxContour,true);
    // Anzahl Ecken
    regionRaw[5]=countCorners(maskSingleRegion);
    // Area minBoundingRect
    regionRaw[6]=minBoundingMaskRect.size.area();
    // Area boundingRect
    regionRaw[7]=boundingMaskRect.height*boundingMaskRect.width;
    // Area boundingEllipse
    regionRaw[8]=boundingEllipseMask.size.area();
    // aspekt Ratio Bounding Rect
    regionRaw[9]=boundingMaskRect.height/boundingMaskRect.width;
    // extend
    regionRaw[11]= imageMoments.m00/(boundingMaskRect.height*boundingMaskRect.width);
    // qDebug() << "Verhaeltnis Umfang-Flaeche " << regionRaw[4]/regionRaw[3];
    return regionRaw;
}

int DetectProcessor::countCorners(Mat& image){
    // https://github.com/arnaudgelas/OpenCVExamples/blob/master/cvMat/GoodFeaturesToTrack/GoodFeaturesToTrack.cpp
    std::vector< cv::Point2f > corners;

    // maxCorners – The maximum number of corners to return. If there are more corners
    // than that will be found, the strongest of them will be returned
    int maxCorners = 20;

    // qualityLevel – Characterizes the minimal accepted quality of image corners;
    // the value of the parameter is multiplied by the by the best corner quality
    // measure (which is the min eigenvalue, see cornerMinEigenVal() ,
    // or the Harris function response, see cornerHarris() ).
    // The corners, which quality measure is less than the product, will be rejected.
    // For example, if the best corner has the quality measure = 1500,
    // and the qualityLevel=0.01 , then all the corners which quality measure is
    // less than 15 will be rejected.
    double qualityLevel = 0.015;

    // minDistance – The minimum possible Euclidean distance between the returned corners
    double minDistance = 60.;

    // mask – The optional region of interest. If the image is not empty (then it
    // needs to have the type CV_8UC1 and the same size as image ), it will specify
    // the region in which the corners are detected
    cv::Mat mask;

    // blockSize – Size of the averaging block for computing derivative covariation
    // matrix over each pixel neighborhood, see cornerEigenValsAndVecs()
    int blockSize = 8;

    // useHarrisDetector – Indicates, whether to use operator or cornerMinEigenVal()
    bool useHarrisDetector = false;

    // k – Free parameter of Harris detector
    double k = 0.04;
    cv::goodFeaturesToTrack( image, corners, maxCorners, qualityLevel, minDistance, mask, blockSize, useHarrisDetector, k );
    return corners.size();
}



