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
    test();
}

ProjectAWidget::~ProjectAWidget()
{
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

}

void ProjectAWidget::test(){
    qDebug() << "Test ";
}

void ProjectAWidget::on_pushButton_clicked()
{
    videoThread->start();
}

void ProjectAWidget::on_masterVolSlider_valueChanged(int value)
{

}
