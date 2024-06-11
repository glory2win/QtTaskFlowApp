#pragma once

#include <QLabel>
#include <QWidget>
#include "ui_TestWidget.h"

namespace Tests
{
	class TestListItem : public QWidget
	{
	public:
		TestListItem(QWidget* parent);
		~TestListItem() = default;

	private:
		QLabel* m_iconLabel;
		QLabel* m_label;
	};

	class TestWidget : public QWidget
	{
		Q_OBJECT

	public:
		TestWidget(QWidget* parent = nullptr);
		~TestWidget();

	private:
		Ui::TestWidget ui;
	};
}