#pragma once

#include <models/DataManager.h>
#include <views/TaskFlowView.h>

class TaskFlowPresenter : public QObject
{
	Q_OBJECT

public:
	explicit TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent = nullptr);

	~TaskFlowPresenter() override = default;

private slots:
	void onCategoryNameChanged(const QString& rename);
	void onNewCategoryAdded(const QString& name);

private:
	DataManager* m_model;
	TaskFlowView* m_view;
};
