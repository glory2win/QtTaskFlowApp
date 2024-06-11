#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskFlow.h"

#include <QPushButton>
#include "CategoryListView.h"

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


	signals:
		void newCategoryAdded(const QString& categoryName);
		void categorySelected(int categoryIndex);
		void todoAdded(int categoryId, const QString& todoText);

	public slots:
		void onCategoryNameUpdated(const QString& rename);
		void onTodoTextUpdated(const QString& rename);

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
