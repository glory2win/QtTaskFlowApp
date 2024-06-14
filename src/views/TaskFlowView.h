#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskFlow.h"

#include <QPushButton>
#include "CategoryListView.h"
#include "models/DataManager.h"



namespace View
{
	class TaskFlowView : public QWidget
	{
		Q_OBJECT

	public:
		explicit TaskFlowView(QWidget* parent = nullptr);
		~TaskFlowView() override = default;

		int getSelectedCategoryIndex() const;
		bool isValidCategorySelected();

		// ******************* SAVE & LOAD SUPPORT *******************
		void addCategoryItem(const QString& categoryName);
		void addTodoItem(const Model::Data::TodoItemData& todoData);

		void updateCategoryList();

		void clearTotoList();


	signals:
		// Signals for presenter
		void newCategoryAdded(const QString& categoryName);
		void categoryNameChanged(const QString& newCategoryName);

		void categorySelected(const CategoryListItem* categoryItem);

		void todoAdded(const QString& categoryName, const QString& todoText);
		void updateTodoDoneStatus(int todoIndex, bool done); // Assuming the to do item has belongs to selected category.
		void updateTodoImpStatus(int todoIndex, bool imp);

		

	public slots:
		// Category item signals slot
		void onCategoryNameUpdated(const QString& rename);
		void onUpdateAllCategoryNames(QList<QString> list);

		// To do item's signals slots
		void onTodoTextUpdated(const QString& rename);
		void onTodoItemDoneStatusUpdated(int todoIndex, bool done);
		void onTodoItemImpStatusUpdated(int todoIndex, bool imp);

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

		CategoryListItem* m_selectedCategory;
		int m_selectedCategoryIndex;
	};
}
