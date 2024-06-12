#include "TaskFlowView.h"

#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

#include "CategoryListView.h"
#include "TodoListView.h"
#include <QListWidgetItem>
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
	}


	// *********************** SLOTS ************************************

	void TaskFlowView::onSettingBtnPressed()
	{
		qDebug() << "[Settings] - Settings button pressed " << __FUNCTION__;
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
				emit categorySelected(m_selectedCategoryIndex);
				// The category data manipulation and ui update is handling in the presenter.

				//qDebug() << "Selected Category: [index: " << m_selectedCategoryIndex << "] name: [" << m_selectedCategory->getCategoryName() << "] has items: [" << m_selectedCategory->getd
			}
			catItem->setSelected(item->isSelected());
		}
	}

	void TaskFlowView::onCategoryListItemClicked()
	{
	}

	void TaskFlowView::onTodoItemAdded(const QString& todoText)
	{
		if (todoText.isEmpty() || !isValidCategorySelected())
		{
			return;
		}
		qDebug() << "A new todo item has been added to the list." << __FUNCTION__;

		TodoListItem* itemWidget = new TodoListItem(this, ui.todoList);
		QListWidgetItem* item = new QListWidgetItem(ui.todoList);
		item->setSizeHint(itemWidget->sizeHint());
		ui.todoList->setItemWidget(item, itemWidget);

		itemWidget->setTotoText(todoText);

		emit todoAdded(m_selectedCategoryIndex, itemWidget->getTodoText());
	}

	void TaskFlowView::onCategoryNameUpdated(const QString& rename)
	{
		qDebug() << "Catgory name has updated to: [" << rename << "] Func: " << __FUNCTION__;
		ui.categoryTitleLabel->setText(rename);
	}

	void TaskFlowView::onTodoTextUpdated(const QString& rename)
	{
		qDebug() << "Todo name has updated to: [" << rename << "] Func: " << __FUNCTION__;
	}

	// *********************** PUBLIC FUNCTIONS ************************************

	bool TaskFlowView::isValidCategorySelected()
	{
		bool categoryValid = ui.categoryList->count() != 0 && m_selectedCategory != nullptr;
		return categoryValid;
	}

	void TaskFlowView::addCategoryItem(const QString& categoryName)
	{
		CategoryListItem* itemWidget = new CategoryListItem(this, ui.categoryList);
		QListWidgetItem* item = new QListWidgetItem(ui.categoryList);
		item->setSizeHint(itemWidget->sizeHint());
		ui.categoryList->setItemWidget(item, itemWidget);

		itemWidget->setCategoryName(categoryName);
	}

	void TaskFlowView::addTodoItem(const QString& categoryName, const Model::Data::TodoItemData& todoData)
	{
		TodoListItem* itemWidget = new TodoListItem(this, ui.todoList);
		QListWidgetItem* item = new QListWidgetItem(ui.todoList);
		item->setSizeHint(itemWidget->sizeHint());
		ui.todoList->setItemWidget(item, itemWidget);

		itemWidget->setTotoText(todoData.todo);
		itemWidget->setImportantStatus(todoData.isImportant);
		itemWidget->setCompletedStatus(todoData.isCompleted);

		itemWidget->setEditable(false);

	}

	void TaskFlowView::updateLists()
	{
		QListWidgetItem* item = ui.categoryList->item(0);
		CategoryListItem* catItem = qobject_cast<CategoryListItem*>(ui.categoryList->itemWidget(item));
		catItem->setSelected(true);

	}
}
