#include "projectafactory.h"

#include "abstractprojectinfo.h"
#include "a/projectawidget.h"

AbstractProjectInfo* ProjectAFactory::createProjectInfo()
{
    return new AbstractProjectInfo("Project A");
}
AbstractProjectWidget* ProjectAFactory::createProjectWidget()
{
   return createProjectWidget(0, createProjectInfo());
}

AbstractProjectWidget* ProjectAFactory::createProjectWidget(QWidget *parent, AbstractProjectInfo *projectInfo) {
    return new ProjectAWidget(parent, projectInfo);
}

