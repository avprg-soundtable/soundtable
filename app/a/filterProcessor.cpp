#include "filterProcessor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <QDebug>
using namespace cv;


FilterProcessor::FilterProcessor()
    : useMedian(true)
    , useOpening(true)
    , useNoiseRecution(true)
    , useEqualization(false)
    , bufferMode(true)
    , frameCount(0)
    , alpha(1)
    , beta(0)
    , fTau(0.65)
    , bufferSize(2)
{
    pMOG2 = new cv::BackgroundSubtractorMOG2(500,20,true);
    pMOG2->setDouble("fTau",0.65);
    pMOG2->setDouble("varThresholdGen",16);

}
FilterProcessor::~FilterProcessor()
{
}
void FilterProcessor::setAlpha(double pAlpha){
    alpha=pAlpha;
}

void FilterProcessor::setBeta(int pBeta){
    beta=pBeta;
}

void FilterProcessor::setBufferSize(int pBufferSize){
    bufferSize=pBufferSize;
}


void FilterProcessor::setUseEqualization(bool enable){
    useEqualization=enable;
}

void FilterProcessor::setSigmaBackground(int pSigma){
    sigmaBackground=pSigma;
    pMOG2->setDouble("varThresholdGen",sigmaBackground);
}

void FilterProcessor::setfTau(double pfTau){
    fTau=pfTau;
    pMOG2->setDouble("fTau",fTau);
}

Mat FilterProcessor::preProcess(const Mat &input){
    Mat frame;
    input.convertTo(frame, -1, alpha, beta);
    if (useEqualization){
        frame=equalization(frame);
    }
    return frame;
}

Mat FilterProcessor::process(const Mat &input){
    Mat binaryMask;
    Mat frame;
    input.copyTo(frame);
    if(bufferMode){
        if (frameCount==0){
            // perform filter
            binaryMask = filter(frame);
            if (useMedian){
                medianBlur(binaryMask, binaryMask, 5);
            }
            if (useOpening){
                erode(binaryMask, binaryMask, Mat());
                dilate(binaryMask, binaryMask, Mat());
            }
            if(useNoiseRecution){
               binaryMask=noiseRecution(binaryMask);
            }
            // set Buffer Frame
            bufferFrame=binaryMask;
            return binaryMask;
        }else{
            if (frameCount==bufferSize){
                frameCount=0;
             }
            return bufferFrame;
        }
    }else{
        // perform filter
        binaryMask = filter(frame);

        if (useMedian){
            medianBlur(binaryMask, binaryMask, 5);
        }

        if (useOpening){
            erode(binaryMask, binaryMask, Mat());
            dilate(binaryMask, binaryMask, Mat());
        }

        if(useNoiseRecution){
           binaryMask=noiseRecution(binaryMask);
        }

        return binaryMask;
    }
     frameCount=frameCount+1;
   }
Mat FilterProcessor::filter(Mat& frame){

    Mat fgMaskMOG2;
    Mat frametoProcess;
    Mat frameGray;
    cvtColor(frame, frametoProcess, CV_BGR2GRAY);
    pMOG2->operator ()(frametoProcess,fgMaskMOG2,0);
    fgMaskMOG2 = removeShadows(fgMaskMOG2);
    return fgMaskMOG2;
}

Mat FilterProcessor::removeShadows(Mat& frame){

    Mat frameToProcess;
    frame.copyTo(frameToProcess);
    for(int x = 0; x < frameToProcess.cols; x++){
            for(int y = 0; y < frameToProcess.rows; y++){
               if (frameToProcess.at<uchar>(y,x) <= 127) {
                   frameToProcess.at<uchar>(y,x)=0;
               }
            }
    }

    return frameToProcess;
}


void FilterProcessor::reinitializeBG(Mat& background){
    //not working so far
    Mat ignoreMask;
    Mat frametoProcess;
    background.copyTo(frametoProcess);
    //frametoProcess=equalization(background);
    pMOG2 = NULL;
    pMOG2 = new cv::BackgroundSubtractorMOG(5000,0,0.1,0);
    pMOG2->operator ()(frametoProcess,ignoreMask,1);
    pMOG2->operator ()(frametoProcess,ignoreMask,0);
}


Mat FilterProcessor::equalization(Mat& frame){
    Mat frametoProcess;
    vector<Mat> channels;
    cvtColor(frame, frametoProcess, CV_BGR2YCrCb);
    split(frametoProcess,channels);
    equalizeHist(channels[0], channels[0]);
    merge(channels,frametoProcess);
    cvtColor(frametoProcess, frametoProcess, CV_YCrCb2BGR);
    return frametoProcess;
}

Mat FilterProcessor::noiseRecution(Mat& binaryMask){
    Mat copyOfMask;
    binaryMask.copyTo(copyOfMask);

        // find all regions
        vector<vector<Point> >contours;
        findContours(copyOfMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

        // erase small regions

        for(int i = 0; i < contours.size(); i++){
            vector<Point>contour = contours[i];
            int area = contourArea(contour);
            if (area <= 64){
                drawContours(binaryMask, contours, i, Scalar(0, 0, 0, 0), CV_FILLED);
            }
        }

       return binaryMask;

}
void FilterProcessor::setUseBufferMode(bool enable){
    this->bufferMode=enable;
}

void FilterProcessor::setUseNoiseReduction(bool enable){
    this->useNoiseRecution=enable;
}

void FilterProcessor::setMedianEnable(bool enable){
    this->useMedian = enable;
}

void FilterProcessor::setOpeningEnable(bool enable){
    this->useOpening = enable;
}
