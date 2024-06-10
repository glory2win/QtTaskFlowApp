#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskFlow.h"

#include <QPushButton>

class TaskFlowView : public QWidget
{
	Q_OBJECT

public:
	explicit TaskFlowView(QWidget* parent = nullptr);
	~TaskFlowView() override = default;

	int getSelectedCategoryIndex() const;


signals:
	void categoryAdded(const QString& categoryName);
	void todoAdded(int categoryId, const QString& todoText);

public slots:
	void onCategoryNameUpdated(const QString& rename);
	void onTodoTextUpdated(const QString& rename);


private slots:
	void onSettingBtnPressed();
	void onListOptionBtnPressed();

	void onAddCategoryBtnPressed();
	void onCategoryListItemSelectionChanged();
	void onCategoryListItemClicked();

	void onTodoItemAdded(const QString& todoText);

private:
	Ui::TaskFlowClass ui;
	void setupUi() const;
	void connectUi();
};
