#include "ThemeManager.h"
#include "CategoryListItem.h"

#include <QHBoxLayout>



#pragma region LINE_EDIT
CategoryLineEdit::CategoryLineEdit(QWidget* parent): QLineEdit(parent)
{
	this->setFont(ThemeManager::instance().titleFont());
	this->setText("Untitled");
}

void CategoryLineEdit::focusOutEvent(QFocusEvent* event)
{
	QLineEdit::focusOutEvent(event); // Since this automatically calls the void CategoryListItem::setEditable(bool enabled), foucChanged has no need but keep it for reference.
	emit focusChanged();
}

#pragma endregion LINE_EDIT


#pragma region LIST_ITEM
CategoryListItem::CategoryListItem(QWidget* parent) : QWidget(parent)
{
	m_iconLabel = new QLabel(this);
	m_categoryLineEdit = new CategoryLineEdit(this);


	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_iconLabel);
	layout->addWidget(m_categoryLineEdit);

	setLayout(layout);

	connect(m_categoryLineEdit, &QLineEdit::editingFinished, [&]()
	{
		setEditable(false);
	});

	QObject::connect(m_categoryLineEdit, &CategoryLineEdit::focusChanged, this, &CategoryListItem::handleLostFocus);
}

void CategoryListItem::setCategoryName(const QString& rename) const
{
	// TODO: check all categories list if name already available then append number. Eg: Untitle 2
	m_categoryLineEdit->setText(rename);
}

// Call when Rename option selected.
void CategoryListItem::setEditable(const bool enabled) const
{
	if (m_categoryLineEdit)
	{
		if (enabled)
		{
			m_categoryLineEdit->selectAll();
			m_categoryLineEdit->setReadOnly(false);
			m_categoryLineEdit->setFocus();
			m_categoryLineEdit->setFrame(true);
			m_categoryLineEdit->setEnabled(true);
		}
		else
		{
			m_categoryLineEdit->setReadOnly(true);
			m_categoryLineEdit->clearFocus();
			m_categoryLineEdit->setFrame(false);
			m_categoryLineEdit->setEnabled(false);
		}
	}
}

void CategoryListItem::handleLostFocus()
{
	qDebug() << "Focus has lost";
}

#pragma endregion LIST_ITEM
