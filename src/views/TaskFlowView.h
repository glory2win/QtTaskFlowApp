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

		void addCategoryItem(const QString& categoryName);
		void addTodoItem(const Model::Data::TodoItemData& todoData);

		void updateCategoryList();

		void clearTotoList();


	signals:
		void newCategoryAdded(const QString& categoryName);
		void categorySelected(const CategoryListItem* categoryItem);
		void todoAdded(const QString& categoryName, const QString& todoText);

	public slots:
		void onCategoryNameUpdated(const QString& rename);
		void onTodoTextUpdated(const QString& rename);
		void onTodoDoneStatusUpdated(bool done);
		void onTodoCheckStatusUpdated(bool imp);

	private slots:
		void onSettingBtnPressed();
		void onListOptionBtnPressed();

		void onAddCategoryBtnPressed();
		void onCategoryListItemSelectionChanged();
		void onCategoryListItemClicked();

		void onTodoItemAdded(const QString& todoText);
		void onTodoItemMarkedDone(bool done);
		void onTodoItemMarkedImp(bool imp);

	private:
		Ui::TaskFlowClass ui;
		void setupUi() const;
		void connectUi();

		CategoryListItem* m_selectedCategory;
		int m_selectedCategoryIndex;
	};
}
