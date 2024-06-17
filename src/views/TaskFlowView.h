#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskFlow.h"

#include <QPushButton>
#include <QPoint>
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
		void clearCategoryList() const;
		void clearTotoList() const;


	signals:
		// Signals for presenter
		void newCategoryAdded(const QString& categoryName);
		void categoryNameChanged(CategoryListItem* categoryItem, const QString& cachedCategoryName);
		void categorySelected(const CategoryListItem* categoryItem);
		void duplicateCategory(const CategoryListItem* categoryItem);
		void deleteCategory(CategoryListItem* categoryItem);

		void todoAdded(const QString& categoryName, const QString& todoText);
		void updateTodoDoneStatus(int todoIndex, bool done); // Assuming the to do item has belongs to selected category.
		void updateTodoImpStatus(int todoIndex, bool imp);


	public slots:
		// Category item signals slot
		void onCategoryNameUpdated(CategoryListItem* category);
		void onUpdateAllCategoryNames(QList<QString> list);
		void onRenameCategoryRequested();
		void onDeleteCategoryRequested();
		void onDuplicateCategoryRequested();

		// To do item's signals slots
		void onTodoTextUpdated(const QString& rename);
		void onTodoItemDoneStatusUpdated(int todoIndex, bool done);
		void onTodoItemImpStatusUpdated(int todoIndex, bool imp);

		// To do context menu signal slots
		void onTodoEditRequested();
		void onTodoMarkDoneRequested();
		void onTodoMarkImpRequested();
		void onTodoDeleteRequested();


	private slots:
		void onSettingBtnPressed();
		void onListOptionBtnPressed();

		void onAddCategoryBtnPressed();
		void onCategoryListItemSelectionChanged();
		void onCategoryListItemClicked();

		void onTodoItemAdded(const QString& todoText);

	private:
		void showCategoryContextMenu(const QPoint& pos);

	private:
		Ui::TaskFlowClass ui;
		void setupUi() const;
		void connectUi();

		CategoryListItem* m_selectedCategory;
		int m_selectedCategoryIndex;

		QString m_categoryCachedName;
	};
}
