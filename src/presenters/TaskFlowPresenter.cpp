#include "TaskFlowPresenter.h"

namespace Presenter
{
	TaskFlowPresenter::TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent) : QObject(parent),
		m_model(model), m_view(view)
	{
		// Model connections
		connect(model, &DataManager::dataChanged, this, &TaskFlowPresenter::onDataLoaded);

		// View connections
		connect(view, &TaskFlowView::newCategoryAdded, this, &TaskFlowPresenter::onNewCategoryAdded);
		connect(view, &TaskFlowView::categorySelected, this, &TaskFlowPresenter::onCategorySelected);
	}

	void TaskFlowPresenter::onNewCategoryAdded(const QString& name)
	{
		qDebug() << "New Category Added" << __FUNCTION__;
	}

	void TaskFlowPresenter::onCategorySelected(const CategoryListItem* category)
	{
		qDebug() << "[" << category->getCategoryName() << "] has selected" << __FUNCTION__;
		for (auto& catData : m_model->categories)
		{
			if (catData.name == category->getCategoryName())
			{
				m_currCategoryData = &catData; // Cache this as selected category to add to do items later easily.
				m_view->clearTotoList();
				for (const auto& todo : catData.items)
				{
					m_view->addTodoItem(todo);
				}
			}
		}
	}

	void TaskFlowPresenter::onCategoryNameChanged(const QString& rename)
	{
	}

	void TaskFlowPresenter::onDataLoaded()
	{
		qDebug() << "Data has changed: [" << m_model->categories.count() << "] records found!";
		// TODO: read the categories data and make the ui.
		for (const auto& category : m_model->categories)
		{
			m_view->addCategoryItem(category.name);
		}
		m_view->updateCategoryList();
		// This will update the view, the view will trigger to do items creation in this presenter.
	}
}
