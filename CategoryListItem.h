#pragma once

#include <QWidget>
#include <QLabel>

class CategoryListItem : public QWidget
{
	Q_OBJECT

public:
	CategoryListItem(QWidget* parent);
	~CategoryListItem() override = default;

private:

	QLabel* m_arrowPixmapLabel;
	QLabel* m_categoryNameLabel;

};
