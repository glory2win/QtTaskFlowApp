#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskFlow.h"

class TaskFlow : public QWidget
{
    Q_OBJECT

public:
    TaskFlow(QWidget *parent = nullptr);
    ~TaskFlow();

private:
    Ui::TaskFlowClass ui;
};
