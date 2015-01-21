#include "projectawidget.h"
#include "ui_projectawidget.h"
#include <QDebug>

ProjectAWidget::ProjectAWidget(QWidget *parent, AbstractProjectInfo *projectInfo) :
    AbstractProjectWidget(parent, projectInfo),
    ui(new Ui::ProjectAWidget)
  ,videoThread(new VideoEngine)
  ,controlProcessor(new ControlProcessor())
{
    ui->setupUi(this);
    videoThread->setProcessor(controlProcessor);
    connect(videoThread, SIGNAL(sendInputImage(const QImage&)), ui->inputFrame, SLOT(setImage(const QImage&)));
    connect(videoThread, SIGNAL(sendProcessedImage(const QImage&)), ui->outputFrame, SLOT(setImage(const QImage&)));
    updateParameters();
}

ProjectAWidget::~ProjectAWidget()
{
   delete videoThread;
    delete controlProcessor;
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
    qDebug() << "update ";
    controlProcessor->setMasterVol(float(ui->masterVolSlider->value()));
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


