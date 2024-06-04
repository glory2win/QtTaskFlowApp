#include "CategoryListItem.h"

#include <QHBoxLayout>

CategoryListItem::CategoryListItem(QWidget* parent) : QWidget(parent)
{
	m_arrowPixmapLabel = new QLabel(this);
	m_categoryNameLabel = new QLabel(this);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_arrowPixmapLabel);
	layout->addWidget(m_categoryNameLabel);

	setLayout(layout);
}


