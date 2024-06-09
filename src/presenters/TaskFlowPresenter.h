#pragma once

#include <QObject>
#include <models/DataManager.h>
#include <views/TaskFlow.h>
#include <memory>

class TaskFlowPresenter : QObject
{
	Q_OBJECT

public:
	explicit TaskFlowPresenter(
		std::unique_ptr<DataManager> model,
		std::unique_ptr<TaskFlow> view,
		QObject* parent =  nullptr
		);

	~TaskFlowPresenter() override = default;


private slots:
	void onCategoryNameChanged(const QString& rename);

private:
	std::unique_ptr<DataManager> m_model;
	std::unique_ptr<TaskFlow> m_view;
};

