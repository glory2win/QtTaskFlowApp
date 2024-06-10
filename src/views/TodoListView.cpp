#include "TodoListView.h"

#include <QWidget>
#include <QHBoxLayout>

#include "TaskFlowView.h"
#include "utilities/ThemeManager.h"

TodoLineEdit::TodoLineEdit(QWidget* parent) : QLineEdit(parent)
{
	setObjectName("todoLineEdit");
	this->setFont(ThemeManager::instance().itemFont());
	this->setText("");
	this->setFrame(true);
}

TodoListItem::TodoListItem(TaskFlowView* mainView, QWidget* parent) : QWidget(parent),
                                                                      m_starIcon(QString("/images/star.png"))
{
	setObjectName("todoListItem");

	m_completedCheckBox = new QCheckBox(parent);
	m_completedCheckBox->setObjectName("doneCheckBox");

	m_todoLineEdit = new TodoLineEdit(this);
	m_todoLineEdit->setAlignment(Qt::AlignCenter);
	m_todoLineEdit->setAutoFillBackground(true);

	m_impIconBtn = new QPushButton("", this);
	QIcon impIcon(m_starIcon);
	m_impIconBtn->setIcon(impIcon);
	m_impIconBtn->setIconSize(QSize(16, 16));

	auto layout = new QHBoxLayout(this);
	layout->addWidget(m_completedCheckBox);
	layout->addWidget(m_todoLineEdit);
	layout->addWidget(m_impIconBtn);

	layout->setContentsMargins(4, 4, 4, 4);
	layout->setSpacing(6);

	setLayout(layout);

	setEditable(false); // no editing enabled for to do items by default. only through context menu.

	connect(this, &TodoListItem::todoTextUpdated, mainView, &TaskFlowView::onTodoTextUpdated);
	connect(m_todoLineEdit, &QLineEdit::editingFinished, [&]()
	{
		setEditable(false);
		emit todoTextUpdated(m_todoLineEdit->text());
	});
}

QString TodoListItem::getTodoText() const
{
	return m_todoLineEdit->text();
}

void TodoListItem::setTotoText(const QString& rename) const
{
	m_todoLineEdit->setText(rename);
}

void TodoListItem::setEditable(bool enabled) const
{
	if (m_todoLineEdit)
	{
		if (enabled)
		{
			m_todoLineEdit->selectAll();
			m_todoLineEdit->setReadOnly(false);
			m_todoLineEdit->setFocus();
			m_todoLineEdit->setFrame(true);
			m_todoLineEdit->setEnabled(true);
		}
		else
		{
			m_todoLineEdit->setReadOnly(true);
			m_todoLineEdit->clearFocus();
			m_todoLineEdit->setFrame(false);
			m_todoLineEdit->setEnabled(false);
		}
	}
}
