#include "projectawidget.h"
#include "ui_projectawidget.h"
#include <QDebug>

ProjectAWidget::ProjectAWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    AbstractProjectWidget(parent, projectInfo),
    ui(new Ui::ProjectAWidget)
   ,videoThread(new VideoEngine)
   ,controlProcessor(new ControlProcessor)
{
    ui->setupUi(this);
    videoThread->setProcessor(controlProcessor);
    connect(videoThread, SIGNAL(sendInputImage(const QImage&)), ui->inputFrame, SLOT(setImage(const QImage&)));
    connect(videoThread, SIGNAL(sendProcessedImage(const QImage&)), ui->outputFrame, SLOT(setImage(const QImage&)));
    updateParameters();
}

ProjectAWidget::~ProjectAWidget()
{
    delete controlProcessor;
    videoThread->stop();
    delete videoThread;
    delete ui;
}

bool ProjectAWidget::handleOpenCamera(int device){
    videoThread->openCamera(device);
    return true;
}

void ProjectAWidget::handleOpenFile(QString file){
    videoThread->openFile(file);
}

void ProjectAWidget::updateParameters(){
    //UI Interaction
    controlProcessor->setMasterVol(float(ui->masterVolSlider->value()/100.0));
    controlProcessor->filterProcessor->setAlpha(double(ui->aphaPreprocess->value()/10.0));
    controlProcessor->filterProcessor->setBeta(ui->betaPreprocess->value());
    if(ui->HistCB->isChecked()==true){
       controlProcessor->filterProcessor->setUseEqualization(true);
    }else{
        controlProcessor->filterProcessor->setUseEqualization(false);
    }
    controlProcessor->filterProcessor->setSigmaBackground(ui->bgSigma->value());
    controlProcessor->filterProcessor->setfTau(double(ui->bgfTau->value()/100.0));
    if(ui->medianCB->isChecked()==true){
        controlProcessor->filterProcessor->setMedianEnable(true);
    }else{
        controlProcessor->filterProcessor->setMedianEnable(false);
    }
    if(ui->openingCB->isChecked()==true){
        controlProcessor->filterProcessor->setOpeningEnable(true);
    }else{
        controlProcessor->filterProcessor->setOpeningEnable(false);
    }
    if(ui->noiseCB->isChecked()==true){
        controlProcessor->filterProcessor->setUseNoiseReduction(true);
    }else{
        controlProcessor->filterProcessor->setUseNoiseReduction(false);
    }
    if(ui->bufferCB->isChecked()==true){
        controlProcessor->filterProcessor->setUseBufferMode(true);
        ui->bufferSize->setEnabled(true);
    }else{
        controlProcessor->filterProcessor->setUseBufferMode(false);
        ui->bufferSize->setEnabled(false);
    }
    if(ui->muteCB->isChecked()==true){
        ui->masterVolSlider->setValue(0);
    }
    controlProcessor->filterProcessor->setBufferSize(ui->bufferSize->value());
    if(ui->sequenzerCB->isChecked()==true){
        controlProcessor->setMode(1);
        ui->beatSB->setEnabled(true);
    }
    if(ui->addCB->isChecked()==true){
        controlProcessor->setMode(0);
        ui->beatSB->setEnabled(false);
    }

    controlProcessor->setBeat(float(ui->beatSB->value()));
    if(ui->muteCB->isChecked()==true){
        controlProcessor->setMute(1);
    }else{
        controlProcessor->setMute(0);
    }

}



void ProjectAWidget::on_pushButton_clicked()
{
    videoThread->start();
}

