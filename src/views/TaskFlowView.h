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

signals:
    void categoryAdded(const QString& categoryName);
    void todoAdded(int categoryId, const QString& todoText);

private slots:
    void onSettingBtnPressed();
    void onListOptionBtnPressed();
    void onAddCategoryBtnPressed();
    void onCategoryListItemSelectionChanged();
    void onCategoryListItemClicked();

private:
    Ui::TaskFlowClass ui;
    void setupUi() const;
    void connectUi();
};