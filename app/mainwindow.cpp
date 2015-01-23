#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "abstractprojectfactory.h"
#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"
#include "videoengine.h"

#include <QCameraInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

Q_DECLARE_METATYPE(AbstractProjectFactory::PROJECT_FACTORIES)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentProject(AbstractProjectFactory::NO_PROJECT),
    currentProjectWidget(0),
    WINDOW_TITLE("SoundTable")
{
    ui->setupUi(this);
    setWindowTitle(WINDOW_TITLE);
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
    initDevicesMenu();
    initProjectsMenu();
}

MainWindow::~MainWindow()
{
    delete currentProjectInfo;
    delete currentProjectWidget;
    delete ui;
}

void MainWindow::initDevicesMenu() {
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    QList<QCameraInfo> cameraList = QCameraInfo::availableCameras();
    for(int i = 0; i < cameraList.size(); i++) {
        QCameraInfo cameraInfo = cameraList.at(i);
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant(i));
        ui->menuOpenDevice->addAction(videoDeviceAction);
    }
    connect(videoDevicesGroup, SIGNAL(triggered(QAction*)), this, SLOT(openCameraDevice(QAction*)));
}

void MainWindow::initProjectsMenu() {
    QActionGroup *projectsGroup = new QActionGroup(this);

    QAction *projectA = new QAction("Projekt A", projectsGroup);
    projectA->setCheckable(true);
    projectA->setData(QVariant::fromValue(AbstractProjectFactory::PROJECT_A));
    ui->menuProjects->addAction(projectA);

    QAction *projectB = new QAction("Projekt B", projectsGroup);
    projectB->setCheckable(true);
    projectB->setData(QVariant::fromValue(AbstractProjectFactory::PROJECT_B));
    ui->menuProjects->addAction(projectB);

    connect(projectsGroup, SIGNAL(triggered(QAction*)), this, SLOT(openProject(QAction*)));
}

void MainWindow::changeProject(AbstractProjectFactory::PROJECT_FACTORIES newProject)
{
    // Nothing will happen, if the same project is already in use
    if(currentProject == newProject) {
        return;
    }

    // Delete old ProjectInfo and ProjectInfo, if there are one
    if (currentProject != AbstractProjectFactory::NO_PROJECT) {
        ui->stackedProjectsWidget->setCurrentIndex(AbstractProjectFactory::NO_PROJECT);
        ui->stackedProjectsWidget->removeWidget(currentProjectWidget);
        currentProject = AbstractProjectFactory::NO_PROJECT;
        delete currentProjectWidget;
        delete currentProjectInfo;
    }

    // Get the factory for the new project
    AbstractProjectFactory *factory = AbstractProjectFactory::createFactory(newProject);
    currentProject = newProject;
    currentProjectInfo = factory->createProjectInfo();
    currentProjectWidget = factory->createProjectWidget(this, currentProjectInfo);
    ui->stackedProjectsWidget->addWidget(currentProjectWidget);
    ui->stackedProjectsWidget->setCurrentWidget(currentProjectWidget);
    updateWindowTitle();
    // Deconstruct factory after use
    delete factory;
}

void MainWindow::updateWindowTitle()
{
    if (currentProject == AbstractProjectFactory::NO_PROJECT) {
        setWindowTitle(WINDOW_TITLE);
        return;
    }
    QString newTitle = WINDOW_TITLE + " - " + currentProjectInfo->name();
    setWindowTitle(newTitle);
}

void MainWindow::displayNoProjectSelectedError() {
    QMessageBox::warning(
                this,
                "Kein Projekt ausgewählt",
                "Bitte wählen Sie ein Projekt aus dem Projekt-Menü aus.");
}

void MainWindow::openCameraDevice(QAction *action) {
    if(currentProject == AbstractProjectFactory::NO_PROJECT) {
        action->setChecked(false);
        displayNoProjectSelectedError();
        return;
    }
    int device = qvariant_cast<int>(action->data());
    currentProjectWidget->handleOpenCamera(device);
}

void MainWindow::openFile() {
    if (currentProject == AbstractProjectFactory::NO_PROJECT) {
        displayNoProjectSelectedError();
        return;
    }
    QFileDialog fileDialog(
                this,
                tr("Video öffnen"),
                QDir::homePath(),
                tr("Video Dateien (*.wmv *.mpg *mpeg *.avi *.mp4 *.mov"));
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    if(fileDialog.exec()) {
        QString fileName = fileDialog.selectedFiles().at(0);
        currentProjectWidget->handleOpenFile(fileName);
    }
}

void MainWindow::openProject(QAction *action) {
    AbstractProjectFactory::PROJECT_FACTORIES project =
            qvariant_cast<AbstractProjectFactory::PROJECT_FACTORIES>(action->data());
    changeProject(project);
}


