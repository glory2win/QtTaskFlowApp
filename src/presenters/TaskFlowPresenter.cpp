#include "TaskFlowPresenter.h"


TaskFlowPresenter::TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent) : QObject(parent),
	m_model(model), m_view(view)
{
	connect(view, &TaskFlowView::categoryAdded, this, &TaskFlowPresenter::onNewCategoryAdded);
}


void TaskFlowPresenter::onCategoryNameChanged(const QString& rename)
{
}

void TaskFlowPresenter::onNewCategoryAdded(const QString& name)
{
	qDebug() << "New Category Added" << __FUNCTION__;
}
