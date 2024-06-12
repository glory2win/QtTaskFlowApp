#include "TaskFlowPresenter.h"

namespace Presenter
{
	TaskFlowPresenter::TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent) : QObject(parent),
		m_model(model), m_view(view)
	{
		// Model connections
		connect(model, &DataManager::dataChanged, this, &TaskFlowPresenter::onDataChanged);

		// View connections
		connect(view, &TaskFlowView::newCategoryAdded, this, &TaskFlowPresenter::onNewCategoryAdded);
		connect(view, &TaskFlowView::categorySelected, this, &TaskFlowPresenter::onCategorySelected);
	}

	void TaskFlowPresenter::onNewCategoryAdded(const QString& name)
	{
		qDebug() << "New Category Added" << __FUNCTION__;
	}

	void TaskFlowPresenter::onCategorySelected(int categoryIndex)
	{
		qDebug() << "[" << categoryIndex << "] has selected" << __FUNCTION__;
		// TODO: grab the category from the list from loaded json in the memory.
		// TODO: first use sample data.json to display and update the data later plan fresh app install and no data availability.
	}

	void TaskFlowPresenter::onCategoryNameChanged(const QString& rename)
	{
	}

	void TaskFlowPresenter::onDataChanged()
	{
		qDebug() << "Data has changed: [" << m_model->categories.count() << "] records found!";
		// TODO: read the categories data and make the ui.
		for(const auto& category : m_model->categories)
		{
			m_view->addCategoryItem(category.name);
			for(const auto& todo : category.items)
			{
				m_view->addTodoItem(category.name, todo);
			}
		}
		m_view->updateLists();
	}
}
