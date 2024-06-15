#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

namespace View
{
	// Forward declares.
	class TaskFlowView;

	enum class CategoryViewMode
	{
		Normal,
		Editing
	};

	/* This file holds the definitions for custom QListWidget, QListWidgetItem and its children. */

	/* QLineEdit needs to be extended inorder to call the focusOutEvent. */
	class CategoryLineEdit : public QLineEdit
	{
		Q_OBJECT

	public:
		explicit CategoryLineEdit(QWidget* parent);
		~CategoryLineEdit() override = default;

	signals:
		void focusChanged();

	protected:
		void focusOutEvent(QFocusEvent* event) override;
	};

	class CategoryListItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit CategoryListItem(const TaskFlowView* mainView, QWidget* parent);
		~CategoryListItem() override = default;

		QString getCategoryName() const;
		void setCategoryName(const QString& rename) const;
		void setEditable(bool enabled);
		void setSelected(bool isSelected) const;

		CategoryViewMode mode = CategoryViewMode::Normal;

	signals:
		void categoryNameUpdated(CategoryListItem* category);

	private:
		QLabel* m_iconLabel;
		CategoryLineEdit* m_categoryLineEdit;
		QHBoxLayout* m_layout;

		// Pixmap objects - will be destroyed when this object get destroyed.
		class QPixmap m_expandedIcon;
		class QPixmap m_collapsedIcon;

		int m_index;
	};
}
