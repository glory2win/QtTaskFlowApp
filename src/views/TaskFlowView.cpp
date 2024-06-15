#include "TaskFlowView.h"

#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

#include "CategoryListView.h"
#include "TodoListView.h"
#include <QListWidgetItem>

#include "views/ContextMenu.h"
#include "utilities/ThemeManager.h"

namespace View
{
	TaskFlowView::TaskFlowView(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		this->setupUi();
		this->connectUi();
	}

	int TaskFlowView::getSelectedCategoryIndex() const
	{
		return m_selectedCategoryIndex;
	}

	// *********************** UI SETUP ************************************

	void TaskFlowView::setupUi() const
	{
		QPixmap titlePixMap(":/images/TaskFlowAppTitle.png");
		ui.appTitleLabel->setPixmap(titlePixMap);
		ui.appTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

		const QPixmap settingsIconPixmap(":/images/settings.png");
		const QIcon settingsIcon(settingsIconPixmap);
		ui.settingsBtn->setIcon(settingsIcon);
		ui.settingsBtn->setIconSize(QSize(32, 32));
		ui.settingsBtn->setText("");
		ui.settingsBtn->setFlat(false);

		const QPixmap listOptionsPixmap(":/images/menu.png");
		const QIcon listOptionsIcon(listOptionsPixmap);
		ui.listOptionsBtn->setIcon(listOptionsIcon);
		ui.listOptionsBtn->setIconSize(QSize(32, 32));
		ui.listOptionsBtn->setText("");
		ui.listOptionsBtn->setFlat(false);

		const QPixmap categoryBtnPixmap(":/images/new_category.png");
		const QIcon categoryBtnIcon(categoryBtnPixmap);
		ui.addCategoryListBtn->setIcon(categoryBtnIcon);
		ui.addCategoryListBtn->setIconSize(QSize(48, 48));
		ui.addCategoryListBtn->setText("");
		ui.addCategoryListBtn->setFlat(false);

		// Getting fonts from Theme manager
		ThemeManager::instance().titleFont().setPointSize(28);
		ui.categoryTitleLabel->setFont(ThemeManager::instance().titleFont());
		ui.categoryTitleLabel->setText("No Task List");

		ThemeManager::instance().titleFont().setPointSize(12);
		ui.todoItemInput->setFont(ThemeManager::instance().titleFont());
		ui.todoItemInput->setPlaceholderText(QString("Enter your task here.."));
	}

	// *********************** UI CONNECTION ************************************

	void TaskFlowView::connectUi()
	{
		connect(ui.settingsBtn, &QPushButton::clicked, this, &TaskFlowView::onSettingBtnPressed);
		connect(ui.listOptionsBtn, &QPushButton::clicked, this, &TaskFlowView::onListOptionBtnPressed);
		connect(ui.addCategoryListBtn, &QPushButton::clicked, this, &TaskFlowView::onAddCategoryBtnPressed);

		connect(ui.categoryList, &QListWidget::itemSelectionChanged, this,
		        &TaskFlowView::onCategoryListItemSelectionChanged);

		connect(ui.categoryList, &QListWidget::itemClicked, this, &TaskFlowView::onCategoryListItemClicked);

		connect(ui.todoItemInput, &QLineEdit::editingFinished, [&]()
		{
			onTodoItemAdded(ui.todoItemInput->text());
			ui.todoItemInput->clear();
		});

		// Context menus
		ui.categoryList->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(ui.categoryList, &QListWidget::customContextMenuRequested, this, &TaskFlowView::showCategoryContextMenu);
	}


	// *********************** SLOTS ************************************

	void TaskFlowView::onSettingBtnPressed()
	{
		qDebug() << "[Settings] - Settings button pressed " << __FUNCTION__;

		ContextMenu* contextMenu = ContextMenu::instance(this);
		const QPoint& btnPos = ui.settingsBtn->pos();
		contextMenu->exec(ui.settingsBtn->mapToGlobal(btnPos));
	}

	void TaskFlowView::onListOptionBtnPressed()
	{
		qDebug() << "[List Options] - List Options button pressed " << __FUNCTION__;

		// Create label
	}

	void TaskFlowView::onAddCategoryBtnPressed()
	{
		qDebug() << "[Category Lists] - Add category list button pressed " << __FUNCTION__;

		// 1. Instantiate the custom widget.
		CategoryListItem* itemWidget = new CategoryListItem(this, ui.categoryList);

		// 2. In Qt, QListItemWidget is container that accepts the custom widget, this item widget is needed for list widget.
		QListWidgetItem* item = new QListWidgetItem(ui.categoryList);

		// 3. Set size hint to match custom widget
		item->setSizeHint(itemWidget->sizeHint());

		// 4. Now set the custom widget as item widget
		ui.categoryList->setItemWidget(item, itemWidget);

		itemWidget->setEditable(true);
		item->setSelected(true);
		onCategoryListItemSelectionChanged();

		ui.todoList->clear(); // clear the current lists to do as the current list is set by this new category.

		m_selectedCategory = itemWidget;
		m_selectedCategoryIndex = ui.categoryList->count() - 1;

		emit newCategoryAdded(itemWidget->getCategoryName());
	}

	void TaskFlowView::onCategoryListItemSelectionChanged()
	{
		qDebug() << "Item selection changed";

		int itemCount = ui.categoryList->count();
		for (int i = 0; i < itemCount; ++i)
		{
			// To get QWidget, here CategoryListItem wrapped by QListWidgetItem, we need to cast that from itemWidget of QList.
			QListWidgetItem* item = ui.categoryList->item(i);
			CategoryListItem* catItem = qobject_cast<CategoryListItem*>(ui.categoryList->itemWidget(item));
			if (item->isSelected())
			{
				ui.categoryTitleLabel->setText(catItem->getCategoryName());
				m_selectedCategoryIndex = i;
				m_selectedCategory = catItem;
				emit categorySelected(catItem);
			}
			catItem->setSelected(item->isSelected());
		}
	}

	void TaskFlowView::onCategoryListItemClicked()
	{
		QList<QListWidgetItem*> selection = ui.categoryList->selectedItems();
		QListWidgetItem* selected = selection[0];
		if (CategoryListItem* categoryItem = qobject_cast<CategoryListItem*>(
			ui.categoryList->itemWidget(selected)))
		{
			m_selectedCategoryIndex = ui.categoryList->indexFromItem(selected).column();
			m_selectedCategory = categoryItem;
			emit categorySelected(categoryItem);
		}
	}

	void TaskFlowView::onTodoItemAdded(const QString& todoText)
	{
		if (todoText.isEmpty() || !isValidCategorySelected())
		{
			return;
		}
		qDebug() << "A new todo item has been added to the list: " << todoText << __FUNCTION__;

		TodoListItem* itemWidget = new TodoListItem(this, ui.todoList);
		QListWidgetItem* item = new QListWidgetItem(ui.todoList);
		item->setSizeHint(itemWidget->sizeHint());
		ui.todoList->setItemWidget(item, itemWidget);

		itemWidget->setTotoText(todoText);
		// To do Item's id is where it is in the list, this will get the model's data too so assuming its position in the list and category's data are same.
		itemWidget->index = ui.todoList->count() - 1;

		qDebug() << "A new todo: [" << todoText << "] has added with index: [" << itemWidget->index << "]" <<
			__FUNCTION__;

		emit todoAdded(m_selectedCategory->getCategoryName(), itemWidget->getTodoText());
	}

	void TaskFlowView::showCategoryContextMenu(const QPoint& pos)
	{
		QListWidgetItem* item = ui.categoryList->itemAt(pos);
		if (!item)
			return;

		CategoryContextMenu contextMenu(this);
		contextMenu.exec(ui.categoryList->mapToGlobal(pos));
	}


	void TaskFlowView::onCategoryNameUpdated(CategoryListItem* category)
	{
		// TODO: set mode, normal
		if(category->mode == CategoryViewMode::Editing)
		{
			emit categoryNameChanged(category, m_categoryCachedName);
		}
		else
		{
			category->setEditable(false);
			ui.categoryTitleLabel->setText(category->getCategoryName());
		}
		qDebug() << "Category name has updated to: [" << category->getCategoryName() << "] Func: " << __FUNCTION__;

	}

	void TaskFlowView::onUpdateAllCategoryNames(QList<QString> list)
	{
		int itemCount = ui.categoryList->count();
		for (int i = 0; i < itemCount; ++i)
		{
			QListWidgetItem* item = ui.categoryList->item(i);
			CategoryListItem* catItem = qobject_cast<CategoryListItem*>(ui.categoryList->itemWidget(item));
			catItem->setCategoryName(list[i]);
		}
	}

	void TaskFlowView::onRenameCategoryRequested()
	{
		// 1. set the current category edit mode, cache its name, because if rename failed we will set that name back.
		m_categoryCachedName = m_selectedCategory->getCategoryName();
		qDebug() << "Renaming [" << m_categoryCachedName << "] list action";
		m_selectedCategory->setEditable(true);
		// Emit of signal will handle in onCategoryNameUpdate. because that is bound to Finished signal to lineEdit.
	}

	void TaskFlowView::onDeleteCategoryRequested()
	{
		qDebug() << "Delete list action";

	}

	void TaskFlowView::onDuplicateCategoryRequested()
	{
		qDebug() << "Move to list action";

	}

	void TaskFlowView::onTodoTextUpdated(const QString& rename)
	{
		qDebug() << "Todo name has updated to: [" << rename << "] Func: " << __FUNCTION__;
	}

	void TaskFlowView::onTodoItemDoneStatusUpdated(int todoIndex, bool done)
	{
		qDebug() << "Category: [" + m_selectedCategory->getCategoryName() << "] todo id: [" << todoIndex <<
			"] with done status: [" << done << "]";
		emit updateTodoDoneStatus(todoIndex, done);
	}

	void TaskFlowView::onTodoItemImpStatusUpdated(int todoIndex, bool imp)
	{
		qDebug() << "Category: [" + m_selectedCategory->getCategoryName() << "] todo id: [" << todoIndex <<
			"] with imp status: [" << imp << "]";
		updateTodoImpStatus(todoIndex, imp);
	}

	// *********************** PUBLIC FUNCTIONS ************************************

	bool TaskFlowView::isValidCategorySelected()
	{
		bool categoryValid = ui.categoryList->count() != 0 && m_selectedCategory != nullptr;
		return categoryValid;
	}

	// *************** SAVE & LOAD SUPPORT
	void TaskFlowView::addCategoryItem(const QString& categoryName)
	{
		CategoryListItem* itemWidget = new CategoryListItem(this, ui.categoryList);
		QListWidgetItem* item = new QListWidgetItem(ui.categoryList);
		item->setSizeHint(itemWidget->sizeHint());
		ui.categoryList->setItemWidget(item, itemWidget);

		itemWidget->setCategoryName(categoryName);
	}

	void TaskFlowView::addTodoItem(const Model::Data::TodoItemData& todoData)
	{
		TodoListItem* itemWidget = new TodoListItem(this, ui.todoList);
		QListWidgetItem* item = new QListWidgetItem(ui.todoList);
		item->setSizeHint(itemWidget->sizeHint());
		ui.todoList->setItemWidget(item, itemWidget);

		itemWidget->setTotoText(todoData.todo);
		itemWidget->setImportantStatus(todoData.isImportant);
		itemWidget->setCompletedStatus(todoData.isCompleted);

		itemWidget->setEditable(false);
		item->setSelected(true);

		itemWidget->index = ui.todoList->count() - 1;

		qDebug() << "A new todo: [" << todoData.todo << "] has added with index: [" << itemWidget->index << "]" <<
			__FUNCTION__;
	}

	void TaskFlowView::updateCategoryList()
	{
		// Disable all after creation
		const int count = ui.categoryList->count();
		for (int i = 0; i < count; ++i)
		{
			QListWidgetItem* item = ui.categoryList->item(i);
			CategoryListItem* catItem = qobject_cast<CategoryListItem*>(ui.categoryList->itemWidget(item));
			catItem->setEditable(false);
		}

		// Now select one list from either last selection or last updated one or just select top one.
		QListWidgetItem* selectedItem = ui.categoryList->item(0);
		selectedItem->setSelected(true); // make this item selected as widget.
		CategoryListItem* catItemSelected = qobject_cast<CategoryListItem*>(ui.categoryList->itemWidget(selectedItem));

		emit categorySelected(catItemSelected);
		// This will trigger UI creation of to do items from presenter. This syncs with model.
	}

	void TaskFlowView::clearTotoList()
	{
		ui.todoList->clear();
	}
}
