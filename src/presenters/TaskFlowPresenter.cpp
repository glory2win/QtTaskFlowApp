#include "TaskFlowPresenter.h"

namespace Presenter
{
	TaskFlowPresenter::TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent) : QObject(parent),
		m_model(model), m_view(view)
	{
		// Model connections
		connect(model, &DataManager::dataChanged, this, &TaskFlowPresenter::onDataLoaded);
		connect(this, &TaskFlowPresenter::dataSaved, m_model, &DataManager::onDataSaved);

		// From View connections
		connect(view, &TaskFlowView::newCategoryAdded, this, &TaskFlowPresenter::onNewCategoryAdded);
		connect(view, &TaskFlowView::categorySelected, this, &TaskFlowPresenter::onCategorySelected);
		connect(view, &TaskFlowView::todoAdded, this, &TaskFlowPresenter::onTodoAdded);
		connect(view, &TaskFlowView::updateTodoDoneStatus, this, &TaskFlowPresenter::onUpdateTodoDoneStatus);
		connect(view, &TaskFlowView::updateTodoImpStatus, this, &TaskFlowPresenter::onUpdateTodoImpStatus);

		// To View Connections
		connect(this, &TaskFlowPresenter::updateAllCategoryItemNames, m_view, &TaskFlowView::onUpdateAllCategoryNames);
	}

	void TaskFlowPresenter::onNewCategoryAdded(const QString& name)
	{
		qDebug() << "New Category Added" << __FUNCTION__;
		// TODO: find if the category already exists and then append number. Eg Untitled 1, Groceries 2
		QList<QString> list;
		QString categoryName = name;
		for(int i=0; i < m_model->categories.count(); ++i)
		{
			if(m_model->categories[i].name == categoryName)
			{
				categoryName += "_dup"; // to make sure the category names are unique, lets append "_dup" when create or duplicate the category with same name.
			}
			list.append(categoryName);
		}
		m_model->categories.append(Data::Category{categoryName}); // Let's create the object directly in the list to avoid the need of temporary local variables.
		list.append(categoryName); // add the newly created name too.
		m_currCategoryData = &m_model->categories.last(); // Make sure only refer the latest obj from the list, don't refer any local variables as they will get destroyed after this function scope.		
		
		emit updateAllCategoryItemNames(list);
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

	void TaskFlowPresenter::onTodoAdded(const QString& categoryName, const QString& todoText)
	{
		qDebug() << todoText << "has been added to " << categoryName << " list." << __FUNCTION__;
		Data::TodoItemData todoData;
		todoData.todo = todoText;
		todoData.isCompleted = false;
		todoData.isImportant = false;
		m_currCategoryData->items.append(todoData);

		emit dataSaved();
	}

	void TaskFlowPresenter::onUpdateTodoDoneStatus(int todoIndex, bool done)
	{
		qDebug() << "Todo item index [" << todoIndex << "] done status has updated with [ " << done << "] status in the database and saved.";
		if (todoIndex >= 0 && todoIndex < m_currCategoryData->items.count())
		{
			auto& todoData = m_currCategoryData->items[todoIndex];
			todoData.isCompleted = done;
			emit dataSaved();
		}		
	}

	void TaskFlowPresenter::onUpdateTodoImpStatus(int todoIndex, bool imp)
	{
		qDebug() << "Todo item index [" << todoIndex << "] imp status has updated with [ " << imp << "] status in the database and saved.";
		if (todoIndex >= 0 && todoIndex < m_currCategoryData->items.count())
		{
			auto& todoData = m_currCategoryData->items[todoIndex];
			todoData.isImportant = imp;
			emit dataSaved();
		}
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
