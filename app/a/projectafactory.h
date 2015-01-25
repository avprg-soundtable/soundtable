#ifndef PROJECTAFACTORY_H
#define PROJECTAFACTORY_H

#include "abstractprojectfactory.h"
#include "abstractprojectinfo.h"
#include "abstractprojectwidget.h"

class ProjectAFactory : public AbstractProjectFactory
{

public:
    ProjectAFactory() {}


    AbstractProjectInfo* createProjectInfo();
    AbstractProjectWidget* createProjectWidget();
    AbstractProjectWidget* createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo);

};

#endif // PROJECTAFACTORY_H
