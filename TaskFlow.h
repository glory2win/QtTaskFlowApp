#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskFlow.h"

#include <QPushButton>

class TaskFlow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskFlow(QWidget *parent = nullptr);
    ~TaskFlow() override = default;

private slots:
    void onSettingBtnPressed();
    void onListOptionBtnPressed();
    void onAddCategoryBtnPressed();

private:
    Ui::TaskFlowClass ui;
    void setupUi() const;
    void connectUi();
};
