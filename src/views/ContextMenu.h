#pragma once

#include <QWidget>
#include <QMenu>

#include "TaskFlowView.h"

namespace View
{
	class CategoryContextMenu : public QMenu
	{
		Q_OBJECT

	public:
		explicit CategoryContextMenu(TaskFlowView* mainView);
		~CategoryContextMenu() override = default;

	private:

		QAction* renameList;
		QAction* duplicateList;
		QAction* deleteList;
	};

	class TodoContextMenu : public QMenu
	{
		Q_OBJECT

	public:
		explicit TodoContextMenu(TaskFlowView* mainView);
		~TodoContextMenu() override = default;

	private:
		QAction* editTodo;
		QAction* deleteTodo;
		QAction* markDone;
		QAction* markImp;
	};
}
