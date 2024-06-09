#include "utilities/ThemeManager.h"
#include "CategoryListView.h"


#include <QPixmap>


#pragma region LINE_EDIT
CategoryLineEdit::CategoryLineEdit(QWidget* parent): QLineEdit(parent)
{
	setObjectName("categoryLineEdit"); // IMP: to style custom classes we need "objectName" to recognize in css.
	ThemeManager::instance().titleFont().setPointSize(18);
	this->setFont(ThemeManager::instance().titleFont());
	this->setText("Untitled");
	this->setFrame(true);
}

void CategoryLineEdit::focusOutEvent(QFocusEvent* event)
{
	QLineEdit::focusOutEvent(event);
	// Since this automatically calls the void CategoryListItem::setEditable(bool enabled), foucChanged has no need but keep it for reference.
	emit focusChanged();
}

#pragma endregion LINE_EDIT


#pragma region LIST_ITEM
CategoryListItem::CategoryListItem(QWidget* parent) : QWidget(parent),
                                                      m_expandedIcon(QString(":/images/chevron_right.png")),
                                                      m_collapsedIcon(QString(":/images/list.png"))
{
	setObjectName("categoryListItem");

	m_iconLabel = new QLabel(this);
	m_collapsedIcon = m_collapsedIcon.scaled(20, 20);
	m_iconLabel->setPixmap(m_collapsedIcon);

	m_expandedIcon = m_expandedIcon.scaled(20, 20); // Use this to switch between selection modes.

	m_categoryLineEdit = new CategoryLineEdit(this);
	m_categoryLineEdit->setAlignment(Qt::AlignCenter);
	m_categoryLineEdit->setAutoFillBackground(true);


	m_layout = new QHBoxLayout(this);
	m_layout->addWidget(m_iconLabel);
	m_layout->addWidget(m_categoryLineEdit);

	// Adjust the margins and spacing of the layout
	m_layout->setContentsMargins(10, 6, 10, 6);
	m_layout->setSpacing(10); // Space between icon and line edit

	setLayout(m_layout);

	connect(m_categoryLineEdit, &QLineEdit::editingFinished, [&]()
	{
		setEditable(false);
	});
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

void CategoryListItem::setSelected(const bool isSelected) const
{
	if (isSelected)
	{
		m_categoryLineEdit->setStyleSheet("background-color: #D1B374; color: white");
		m_iconLabel->setPixmap(m_expandedIcon);
	}
	else
	{
		m_categoryLineEdit->setStyleSheet("background-color: #C9C1B0; color: black");
		m_iconLabel->setPixmap(m_collapsedIcon);
	}
}

#pragma endregion LIST_ITEM
