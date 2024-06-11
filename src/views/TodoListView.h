#pragma once

#include <QLineEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QPushButton>

namespace View
{
	class TaskFlowView;

	class TodoLineEdit : public QLineEdit
	{
		Q_OBJECT

	public:
		explicit TodoLineEdit(QWidget* parent);
		~TodoLineEdit() override = default;

	private:
	};

	class TodoListItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit TodoListItem(TaskFlowView* mainView, QWidget* parent);
		~TodoListItem() override = default;

		QString getTodoText() const;
		void setTotoText(const QString& rename) const;

		void setEditable(bool enabled) const;

	signals:
		void todoTextUpdated(const QString& rename);

	private:
		QCheckBox* m_completedCheckBox;
		TodoLineEdit* m_todoLineEdit;
		QPushButton* m_impIconBtn;

		class QPixmap m_starIcon;
	};
}
