#include "TestWidget.h"

#include <QListWidgetItem>
#include <QListWidget>

TestListItem::TestListItem(QWidget* parent): QWidget(parent)
{
	m_iconLabel = new QLabel("Hello", this);
	m_label = new QLabel("I am Varma", this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_iconLabel);
	layout->addWidget(m_label);
	setLayout(layout);
}

TestWidget::TestWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	for(auto i=0; i < 5 ; ++i)
	{
		QListWidgetItem* item = new  QListWidgetItem("Varma", ui.listWidget);
		ui.listWidget->addItem(item);
	}

	TestListItem* itemWidget = new TestListItem(ui.listWidget);

	QListWidgetItem* item = new  QListWidgetItem(ui.listWidget);

	item->setSizeHint(itemWidget->sizeHint());

	ui.listWidget->setItemWidget(item, itemWidget);

}

TestWidget::~TestWidget()
{
}
