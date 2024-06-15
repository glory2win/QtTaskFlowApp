#pragma once

#include <QWidget>
#include <QMenu>

namespace View
{
	class ContextMenu : public QMenu
	{
		Q_OBJECT

	public:
		static ContextMenu* instance(QWidget* parent = nullptr);
		void updateMenu(const QString& itemType);

	private slots:
		void onRename();
		void onDelete();
		void onDuplicate();

		void onEdit();
		void onComplete();
		void onMarkImp();
		void onMoveToList();

	private:
		explicit ContextMenu(QWidget* parent);
		~ContextMenu() override = default;

		static ContextMenu* m_instance;

		void setupActions();

		// Common actions
		QAction* rename;
		QAction* deleteItem;

		// Category Item context options
		QAction* duplicateList;

		// To do item context options
		QAction* edit;
		QAction* markAsImportant;
		QAction* markAsDone;
		QAction* moveToAnotherList;
	};

	class CategoryContextMenu : public QMenu
	{
		Q_OBJECT

	public:
		explicit CategoryContextMenu(QWidget* parent);
		~CategoryContextMenu() override = default;

	private slots:
		void onRenameList();
		void onDeleteList();
		void onDuplicateList();

	private:

		QAction* renameList;
		QAction* deleteList;
		QAction* duplicateList;
	};
}
