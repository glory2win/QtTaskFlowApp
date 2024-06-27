#include "TaskFlowPresenter.h"
#include <QMessageBox>

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
		connect(view, &TaskFlowView::categoryNameChanged, this, &TaskFlowPresenter::onCategoryNameChanged);
		connect(view, &TaskFlowView::duplicateCategory, this, &TaskFlowPresenter::onDuplicateCategory);
		connect(view, &TaskFlowView::deleteCategory, this, &TaskFlowPresenter::onDeleteCategory);
		connect(view, &TaskFlowView::deleteTodo, this, &TaskFlowPresenter::onDeleteTodo);

		// To View Connections
		connect(this, &TaskFlowPresenter::updateAllCategoryItemNames, m_view, &TaskFlowView::onUpdateAllCategoryNames);
	}

	void TaskFlowPresenter::onNewCategoryAdded(const QString& name)
	{
		qDebug() << "New Category Added" << __FUNCTION__;
		// TODO: find if the category already exists and then append number. Eg Untitled 1, Groceries 2
		QList<QString> list;
		QString categoryName = name;
		for (int i = 0; i < m_model->categories.count(); ++i)
		{
			if (m_model->categories[i].name == categoryName)
			{
				categoryName += "_dup";
				// to make sure the category names are unique, lets append "_dup" when create or duplicate the category with same name.
			}
			list.append(categoryName);
		}
		m_model->categories.append(Data::Category{categoryName});
		// Let's create the object directly in the list to avoid the need of temporary local variables.
		list.append(categoryName); // add the newly created name too.
		m_currCategoryData = &m_model->categories.last();
		// Make sure only refer the latest obj from the list, don't refer any local variables as they will get destroyed after this function scope.

		emit updateAllCategoryItemNames(list);
	}

	void TaskFlowPresenter::updateTodoList(Data::Category& catData) const
	{
		m_view->clearTotoList();
		for (const auto& todo : catData.items)
		{
			m_view->addTodoItem(todo);
		}
	}

	void TaskFlowPresenter::onCategorySelected(const CategoryListItem* category)
	{
		if (!category)
			return;

		qDebug() << "[" << category->getCategoryName() << "] has selected" << __FUNCTION__;
		for (auto& catData : m_model->categories)
		{
			if (catData.name == category->getCategoryName())
			{
				m_currCategoryData = &catData; // Cache this as selected category to add to do items later easily.
				updateTodoList(catData);
			}
		}
	}

	void TaskFlowPresenter::onCategoryNameChanged(CategoryListItem* categoryItem, const QString& oldName)
	{
		if (!categoryItem)
			return;

		// TODO check all category names if exists warn user to choose different
		const QString& currName = categoryItem->getCategoryName();
		for (const auto& category : m_model->categories)
		{
			if (category.name == currName) // compare with already applied ui's name.
			{
				categoryItem->setCategoryName(oldName);
				// reset to old name because the proposed new name is already in the list.
				categoryItem->setEditable(false);
				QString msg = QString(
						"There is already a category with the same name: %1.\n Please choose different name!").
					arg(currName);
				QMessageBox::information(m_view, "Duplicate Entry",
				                         "There is already a category with the same name.\n Please choose different name!");
				return;
			}
		}

		if (m_currCategoryData == nullptr)
			return;

		m_currCategoryData->name = categoryItem->getCategoryName();
		categoryItem->setEditable(false);
		emit dataSaved();
	}

	void TaskFlowPresenter::onDuplicateCategory()
	{
		if (!m_currCategoryData)
			return;

		// Make a new category with supplied category name and copy all to do items.
		const Data::Category* originalData = m_currCategoryData;
		auto itemsToCopy = m_currCategoryData->items;
		onNewCategoryAdded(originalData->name);
		for (const auto& elm : itemsToCopy)
		{
			Data::TodoItemData todoData;
			todoData.todo = elm.todo;
			todoData.isImportant = elm.isImportant;
			todoData.isCompleted = elm.isCompleted;
			m_currCategoryData->items.append(todoData);
		}
		onDataLoaded();
		emit dataSaved();
	}

	void TaskFlowPresenter::onDeleteCategory()
	{
		if (!m_currCategoryData)
			return;

		int categoryIndex = -1;
		for (int i = 0; i < m_model->categories.count(); ++i)
		{
			if (m_model->categories[i].name == m_currCategoryData->name)
			{
				categoryIndex = i;
				break;
			}
		}
		if (categoryIndex != -1)
		{
			m_model->categories[categoryIndex].items.clear();
			m_model->categories.removeAt(categoryIndex);
			onDataLoaded();
			emit dataSaved();
		}
		else
		{
			qWarning() << "Unable to find the correct category with the name: [" << m_currCategoryData->name << "]" <<
				__FUNCTION__;
		}
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
		qDebug() << "Todo item index [" << todoIndex << "] done status has updated with [ " << done <<
			"] status in the database and saved.";
		if (todoIndex >= 0 && todoIndex < m_currCategoryData->items.count())
		{
			auto& todoData = m_currCategoryData->items[todoIndex];
			todoData.isCompleted = done;
			emit dataSaved();
		}
	}

	void TaskFlowPresenter::onUpdateTodoImpStatus(int todoIndex, bool imp)
	{
		qDebug() << "Todo item index [" << todoIndex << "] imp status has updated with [ " << imp <<
			"] status in the database and saved.";
		if (todoIndex >= 0 && todoIndex < m_currCategoryData->items.count())
		{
			auto& todoData = m_currCategoryData->items[todoIndex];
			todoData.isImportant = imp;
			emit dataSaved();
		}
	}

	void TaskFlowPresenter::onDeleteTodo(TodoListItem* todoItem)
	{
		qDebug() << "Todo with index: " << todoItem->index << " from " << m_currCategoryData->name << " is deleting..";
		int index = todoItem->index;
		if (index >= 0 && index < m_currCategoryData->items.count())
		{
			m_currCategoryData->items.removeAt(index);
		}
		updateTodoList(*m_currCategoryData);
		emit dataSaved();
	}

	void TaskFlowPresenter::onDataLoaded()
	{
		qDebug() << "Data has changed: [" << m_model->categories.count() << "] records found!";
		// TODO: read the categories data and make the ui.
		m_view->clearCategoryList();
		for (const auto& category : m_model->categories)
		{
			m_view->addCategoryItem(category.name);
		}
		m_view->updateCategoryList();
		// This will update the view, the view will trigger to do items creation in this presenter.
	}
}
