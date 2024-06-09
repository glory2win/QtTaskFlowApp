#include "TaskFlowView.h"

#include <QPixmap>
#include <QIcon>
#include <QMessageBox>

#include "CategoryListView.h"
#include <QListWidgetItem>
#include "utilities/ThemeManager.h"

TaskFlow::TaskFlow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setupUi();
	this->connectUi();
}

void TaskFlow::setupUi() const
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

void TaskFlow::connectUi()
{
	connect(ui.settingsBtn, &QPushButton::clicked, this, &TaskFlow::onSettingBtnPressed);
	connect(ui.listOptionsBtn, &QPushButton::clicked, this, &TaskFlow::onListOptionBtnPressed);
	connect(ui.addCategoryListBtn, &QPushButton::clicked, this, &TaskFlow::onAddCategoryBtnPressed);
	connect(ui.categoryList, &QListWidget::itemSelectionChanged, this, &TaskFlow::onCategoryListItemSelectionChanged);
	connect(ui.categoryList, &QListWidget::itemClicked, this, &TaskFlow::onCategoryListItemClicked);
}


// Slots

void TaskFlow::onSettingBtnPressed()
{
	qDebug() << "[Settings] - Settings button pressed " << __FUNCTION__;
}

void TaskFlow::onListOptionBtnPressed()
{
	qDebug() << "[List Options] - List Options button pressed " << __FUNCTION__;

	// Create label
}

void TaskFlow::onAddCategoryBtnPressed()
{
	qDebug() << "[Category Lists] - Add category list button pressed " << __FUNCTION__;

	// 1. Instantiate the custom widget.
	CategoryListItem* itemWidget = new CategoryListItem(ui.categoryList);

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

void TaskFlow::onCategoryListItemSelectionChanged()
{
	qDebug() << "Item selection changed";

	int itemCount = ui.categoryList->count();
	for (int i = 0; i < itemCount; ++i)
	{
		// To get QWidget, here CategoryListItem wrapped by QListWidgetItem, we need to cast that from itemWidget of QList.
		QListWidgetItem* item = ui.categoryList->item(i);
		CategoryListItem* catItem = qobject_cast<CategoryListItem*>(ui.categoryList->itemWidget(item));
		catItem->setSelected(item->isSelected());

	}
}

void TaskFlow::onCategoryListItemClicked()
{

}
