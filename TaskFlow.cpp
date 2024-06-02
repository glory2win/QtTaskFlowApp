#include "TaskFlow.h"
#include <QPixmap>

TaskFlow::TaskFlow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    QPixmap titlePixMap(":/images/TaskFlowAppTitle.png");
    ui.appTitleLabel->setPixmap(titlePixMap);

}

TaskFlow::~TaskFlow()
{}
