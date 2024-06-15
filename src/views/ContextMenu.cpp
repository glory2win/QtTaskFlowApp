#include "ContextMenu.h"

namespace View
{
	ContextMenu* ContextMenu::m_instance = nullptr;

	ContextMenu::ContextMenu(QWidget* parent) : QMenu(parent)
	{
		/*
		rename = new QAction("Rename", this);
		deleteItem = new QAction("Delete", this);
		duplicateList = new QAction("Duplicate", this);

		edit = new QAction("Edit", this);
		markAsDone = new QAction("Mark as Complete", this);
		markAsImportant = new QAction("Mark as Important", this);
		moveToAnotherList = new QAction("Move to List...", this);
	*/

		setupActions();
	}


	void ContextMenu::setupActions()
	{
		rename = addAction("Rename");
		deleteItem = addAction("Delete");
		duplicateList = addAction("Duplicate");

		edit = addAction("Edit");
		markAsDone = addAction(("Mark as Complete"));
		markAsImportant = addAction("Mark as Important");
		moveToAnotherList = addAction("Move to List...");


		// connect to slots
		connect(rename, &QAction::triggered, this, &ContextMenu::onRename);
		connect(deleteItem, &QAction::triggered, this, &ContextMenu::onDelete);
		connect(duplicateList, &QAction::triggered, this, &ContextMenu::onDuplicate);

		connect(edit, &QAction::triggered, this, &ContextMenu::onEdit);
		connect(markAsDone, &QAction::triggered, this, &ContextMenu::onComplete);
		connect(markAsImportant, &QAction::triggered, this, &ContextMenu::onMarkImp);
		connect(moveToAnotherList, &QAction::triggered, this, &ContextMenu::onMoveToList);
	}



	ContextMenu* ContextMenu::instance(QWidget* parent)
	{
		if(!m_instance)
		{
			m_instance = new ContextMenu(parent);
		}
		return m_instance;
	}

	void ContextMenu::updateMenu(const QString& itemType)
	{

	}

	void ContextMenu::onRename()
	{
		qDebug() << "Rename action";
	}

	void ContextMenu::onDelete()
	{
		qDebug() << "Delete action";

	}

	void ContextMenu::onDuplicate()
	{
		qDebug() << "Duplicate action";

	}

	void ContextMenu::onEdit()
	{
		qDebug() << "Edit action";

	}

	void ContextMenu::onComplete()
	{
		qDebug() << "Done action";

	}

	void ContextMenu::onMarkImp()
	{
		qDebug() << "Mark as imp action";

	}

	void ContextMenu::onMoveToList()
	{
		qDebug() << "Move to list action";

	}


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
}
