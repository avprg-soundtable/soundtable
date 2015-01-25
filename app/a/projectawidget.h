#ifndef PROJECTAWIDGET_H
#define PROJECTAWIDGET_H

#include "abstractprojectwidget.h"
#include "abstractprojectinfo.h"
#include "videoengine.h"
#include "controlProcessor.h"

namespace Ui {
class ProjectAWidget;
}

class ProjectAWidget : public AbstractProjectWidget
{
    Q_OBJECT

public:
    explicit ProjectAWidget(QWidget *parent = 0, AbstractProjectInfo *projectInfo = 0);
    ~ProjectAWidget();

    bool handleOpenCamera(int device) ;
    void handleOpenFile(QString file) ;



private slots:
    void on_pushButton_clicked();
    void updateParameters();

private:
    Ui::ProjectAWidget *ui;
    VideoEngine *videoThread;
    ControlProcessor *controlProcessor;
};

#endif // PROJECTAWIDGET_H
