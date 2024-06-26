#pragma once

#include <QLineEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QPushButton>
#include <memory>

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

		bool getCompletedStatus() const;
		void setCompletedStatus(bool completed) const;

		QString getTodoText() const;
		void setTotoText(const QString& rename) const;

		void setImportantStatus(bool important) const;


		void setEditable(bool enabled) const;

		int index;


	signals:
		void todoTextUpdated(const QString& rename);
		void todoDoneStatusUpdated(int todoIndex, bool done);
		void todoImpStatusUpdated(int todoIndex,bool imp);

	private:
		QCheckBox* m_completedCheck;
		TodoLineEdit* m_todoLineEdit;
		QCheckBox* m_impCheck;

	};
}
