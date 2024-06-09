#include "TaskFlowPresenter.h"

TaskFlowPresenter::TaskFlowPresenter(std::unique_ptr<DataManager> model, std::unique_ptr<TaskFlow> view, QObject* parent)
	: QObject(parent), m_model(std::move(model)), m_view(std::move(view))

{

}

void TaskFlowPresenter::onCategoryNameChanged(const QString& rename)
{

}
