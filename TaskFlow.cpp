#include "TaskFlow.h"

#include <QPixmap>
#include <QIcon>
#include <QFontDatabase>
#include <QMessageBox>

#include "CategoryListItem.h"
#include <QListWidgetItem>
#include "ThemeManager.h"

TaskFlow::TaskFlow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    this->setupUi();
    this->connectUi();
}

TaskFlow::~TaskFlow() = default;


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

    // IMP: When setting up the font with "Arial" kind of notation in QFont will query the font from the computer not from resources
    // In case of custom font, we have to load that first and then create QFont from that. To do that use QFontDatabase class
    if (const int fontId = QFontDatabase::addApplicationFont(":/fonts/Itim-Regular.ttf"); fontId != -1)
        // -1 mean no failure to load the font
    {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.empty())
        {
            const QString& fontName = fontFamilies.at(0); // Get the first one.
            constexpr int fontSize = 28;
            QFont listFont(fontName, fontSize);
            ui.categoryTitleLabel->setFont(listFont);
            ui.categoryTitleLabel->setText("Groceries");

            QFont inputFont(fontName, 12);
            ui.todoItemInput->setFont(inputFont);
            ui.todoItemInput->setPlaceholderText(QString("Enter your task here.."));
        }
        else
        {
            qWarning("[Font] - Font family is empty");
        }
    }
    else
    {
        qWarning("Unable to get the font!");
    }

    // Test - Create Category List items
    for(auto i=0; i < 5; ++i)
    {
        // 1. Instantiate the custom widget.
        CategoryListItem* item = new CategoryListItem(ui.categoryList);
        // 2. In Qt, QListItemWidget is container that accepts the custom widget, this item widget is needed for list widget.
        QListWidgetItem* listItem = new QListWidgetItem(ui.categoryList);
        // 3. Set size hint to match custom widget
        listItem->setSizeHint(item->sizeHint());
        // 4. Now set the custom widget as item widget
        ui.categoryList->setItemWidget(listItem, item);
        ui.categoryList->addItem(listItem);

        /*QListWidgetItem* item = new QListWidgetItem("varma",ui.categoryList);
        ui.categoryList->addItem(item);*/
    }


}

void TaskFlow::connectUi()
{
    connect(ui.settingsBtn, &QPushButton::clicked, this, &TaskFlow::onSettingBtnPressed);
    connect(ui.listOptionsBtn, &QPushButton::clicked, this, &TaskFlow::onListOptionBtnPressed);
    connect(ui.addCategoryListBtn, &QPushButton::clicked, this, &TaskFlow::onAddCategoryBtnPressed);
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
}
