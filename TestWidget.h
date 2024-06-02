#pragma once

#include <QWidget>
#include "ui_TestWidget.h"

class TestWidget : public QWidget
{
	Q_OBJECT

public:
	TestWidget(QWidget *parent = nullptr);
	~TestWidget();

private:
	Ui::TestWidget ui;
};
