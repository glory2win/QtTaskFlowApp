#include "ContextMenu.h"

namespace View
{
	// ********** CATEGORY CONTEXT MENU ****************

	CategoryContextMenu::CategoryContextMenu(TaskFlowView* mainView)  : QMenu(mainView)
	{
		renameList = addAction("Rename");
		duplicateList = addAction("Duplicate");
		addSeparator();
		deleteList = addAction("Delete");

		connect(renameList, &QAction::triggered, mainView, &TaskFlowView::onRenameCategoryRequested);
		connect(duplicateList, &QAction::triggered, mainView, &TaskFlowView::onDuplicateCategoryRequested);
		connect(deleteList, &QAction::triggered, mainView, &TaskFlowView::onDeleteCategoryRequested);

	}

	TodoContextMenu::TodoContextMenu(TaskFlowView* mainView)
	{
		editTodo = addAction("Edit");
		markDone = addAction("Mark as Complete");
		markImp = addAction("Mark as Important");
		addSeparator();
		deleteTodo = addAction("Delete");

		connect(editTodo, &QAction::triggered, mainView, &TaskFlowView::onTodoEditRequested);
		connect(markDone, &QAction::triggered, mainView, &TaskFlowView::onTodoMarkDoneRequested);
		connect(markImp, &QAction::triggered, mainView, &TaskFlowView::onTodoMarkImpRequested);
		connect(deleteTodo, &QAction::triggered, mainView, &TaskFlowView::onTodoDeleteRequested);
	}
}
