#pragma once

#include <models/DataManager.h>
#include <views/TaskFlowView.h>

using namespace Model;
using namespace View;

namespace Presenter
{
	class TaskFlowPresenter : public QObject
	{
		Q_OBJECT

	public:
		explicit TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent = nullptr);

		~TaskFlowPresenter() override = default;

	signals:
		void dataSaved();
		void updateAllCategoryItemNames(QList<QString> nameList);

	private slots:
		//View
		void onNewCategoryAdded(const QString& name);
		void onCategorySelected(const CategoryListItem* category);
		void onCategoryNameChanged(CategoryListItem* categoryItem, const QString& oldName);
		void onDuplicateCategory(); // Assuming the selected (right-clicked) category is going to be duplicated.
		void onDeleteCategory(); // Same

		void onTodoAdded(const QString& categoryName, const QString& todoText);
		void onUpdateTodoDoneStatus(int todoIndex, bool done);
		void onUpdateTodoImpStatus(int todoIndex, bool imp);
		void onDeleteTodo(TodoListItem* todoItem);
		void updateTodoList(Data::Category& catData) const;

		// Model
		void onDataLoaded();

	private:
		DataManager* m_model;
		TaskFlowView* m_view;

		Data::Category* m_currCategoryData = nullptr;
	};
}
