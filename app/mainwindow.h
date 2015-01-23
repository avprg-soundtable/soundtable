#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abstractprojectfactory.h"
#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void initDevicesMenu();
    void initProjectsMenu();

    void changeProject(AbstractProjectFactory::PROJECT_FACTORIES newProject);
    void updateWindowTitle();
    void displayNoProjectSelectedError();

private slots:
    void openCameraDevice(QAction* action);
    void openFile();
    void openProject(QAction* action);

private:
    const QString WINDOW_TITLE;
    Ui::MainWindow *ui;
    AbstractProjectFactory::PROJECT_FACTORIES currentProject;
    AbstractProjectInfo *currentProjectInfo;
    AbstractProjectWidget *currentProjectWidget;
};

#endif // MAINWINDOW_H
