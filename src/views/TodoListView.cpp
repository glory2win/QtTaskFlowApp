#include "TodoListView.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>

#include "TaskFlowView.h"
#include "utilities/ThemeManager.h"

namespace View
{
	TodoLineEdit::TodoLineEdit(QWidget* parent) : QLineEdit(parent)
	{
		setObjectName("todoLineEdit");
		this->setFont(ThemeManager::instance().itemFont());
		this->setText("");
		this->setFrame(true);
	}

	TodoListItem::TodoListItem(TaskFlowView* mainView, QWidget* parent) : QWidget(parent)
	{
		setObjectName("todoListItem");

		m_completedCheckBox = new QCheckBox(parent);
		m_completedCheckBox->setObjectName("doneCheckBox");

		m_todoLineEdit = new TodoLineEdit(this);
		m_todoLineEdit->setAlignment(Qt::AlignCenter);
		m_todoLineEdit->setAutoFillBackground(true);

		m_impIconBtn = new QPushButton("", this);

		QPixmap normalPixmap(":/images/star.png");
		m_starEmptyIcon = std::make_unique<QIcon>(normalPixmap);

		QPixmap filledIcon(":/images/star_filled.png");
		m_starFilledIcon = std::make_unique<QIcon>(filledIcon);

		m_impIconBtn->setIcon(normalPixmap);
		m_impIconBtn->setIconSize(QSize(20, 20));
		m_impIconBtn->setObjectName("impBtn");

		auto layout = new QHBoxLayout(this);
		layout->addWidget(m_completedCheckBox);
		layout->addWidget(m_todoLineEdit);
		layout->addWidget(m_impIconBtn);

		layout->setContentsMargins(4, 3, 4, 3);
		layout->setSpacing(6);

		setLayout(layout);

		setEditable(false); // no editing enabled for to do items by default. only through context menu.

		connect(this, &TodoListItem::todoTextUpdated, mainView, &TaskFlowView::onTodoTextUpdated);
		connect(m_todoLineEdit, &QLineEdit::editingFinished, [&]()
		{
			setEditable(false);
			emit todoTextUpdated(m_todoLineEdit->text());
		});

		connect(m_impIconBtn, &QPushButton::clicked, [&]()
		{
			qDebug() << "Marked as important " << __FUNCTION__;
		});
	}

	bool TodoListItem::getCompletedStatus() const
	{
		return m_completedCheckBox->isChecked();
	}

	void TodoListItem::setCompletedStatus(const bool completed) const
	{
		m_completedCheckBox->setCheckState(completed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
		m_todoLineEdit->setFont(completed? ThemeManager::instance().strikeFont() : ThemeManager::instance().itemFont());
	}

	QString TodoListItem::getTodoText() const
	{
		return m_todoLineEdit->text();
	}

	void TodoListItem::setTotoText(const QString& rename) const
	{
		m_todoLineEdit->setText(rename);
	}

	void TodoListItem::setImportantStatus(bool important) const
	{
		m_impIconBtn->setIcon(important ? *m_starFilledIcon : *m_starEmptyIcon);
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
}
