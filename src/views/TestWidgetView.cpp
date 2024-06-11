#include "TestWidgetView.h"

#include <QListWidgetItem>
#include <QListWidget>

namespace Tests
{
	TestListItem::TestListItem(QWidget* parent) : QWidget(parent)
	{
	}

	TestWidget::TestWidget(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);
	}

	TestWidget::~TestWidget()
	{
	}
}
