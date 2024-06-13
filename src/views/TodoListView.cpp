#include "TodoListView.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>

#include "TaskFlowView.h"
#include "utilities/ThemeManager.h"

namespace View
{
	// ****************** TO DO LINE EDIT **************************

	TodoLineEdit::TodoLineEdit(QWidget* parent) : QLineEdit(parent)
	{
		setObjectName("todoLineEdit");
		this->setFont(ThemeManager::instance().itemFont());
		this->setText("");
		this->setFrame(true);
	}

	// ****************** TO DO LIST ITEM **************************

	TodoListItem::TodoListItem(TaskFlowView* mainView, QWidget* parent) : QWidget(parent)
	{
		// ************* SETUP UI *********************

		setObjectName("todoListItem");

		m_completedCheck = new QCheckBox(this);
		m_completedCheck->setObjectName("doneCheckBox");

		m_todoLineEdit = new TodoLineEdit(this);
		m_todoLineEdit->setAlignment(Qt::AlignCenter);
		m_todoLineEdit->setAutoFillBackground(true);

		m_impCheck = new QCheckBox(this);
		m_impCheck->setObjectName("impCheckBox");

		/*
		QPixmap normalPixmap(":/images/star.png");
		m_starEmptyIcon = std::make_unique<QIcon>(normalPixmap);

		QPixmap filledIcon(":/images/star_filled.png");
		m_starFilledIcon = std::make_unique<QIcon>(filledIcon);

		m_impCheck->setIcon(normalPixmap);
		m_impCheck->setIconSize(QSize(20, 20));
		m_impCheck->setObjectName("impBtn");
		*/

		auto layout = new QHBoxLayout(this);
		layout->addWidget(m_completedCheck);
		layout->addWidget(m_todoLineEdit);
		layout->addWidget(m_impCheck);

		layout->setContentsMargins(4, 3, 4, 3);
		layout->setSpacing(6);

		setLayout(layout);

		setEditable(false); // no editing enabled for to do items by default. only through context menu.


		// ************* CONNECT UI ******************

		connect(this, &TodoListItem::todoTextUpdated, mainView, &TaskFlowView::onTodoTextUpdated);
		connect(this, &TodoListItem::todoDoneStatusUpdated, mainView, &TaskFlowView::onTodoDoneStatusUpdated);

		connect(m_todoLineEdit, &QLineEdit::editingFinished, [&]()
		{
			setEditable(false);
			emit todoTextUpdated(m_todoLineEdit->text());
		});

		connect(m_impCheck, &QPushButton::clicked, [&]()
		{
			qDebug() << "Marked as important " << __FUNCTION__;
		});

		connect(m_completedCheck, &QCheckBox::checkStateChanged, [&]()
		{
			const bool isDone = m_completedCheck->checkState() == Qt::CheckState::Checked;

			m_todoLineEdit->setFont(isDone
				                        ? ThemeManager::instance().strikeFont()
				                        : ThemeManager::instance().itemFont());

			emit todoDoneStatusUpdated(isDone);

			// debug
			QString debugResult = isDone ? "True" : "False";
			qDebug() << "Todo done status: " << debugResult;
		});
	}

	// ****************** SAVE & LOAD SUPPORT **************************

	bool TodoListItem::getCompletedStatus() const
	{
		return m_completedCheck->isChecked();
	}

	void TodoListItem::setCompletedStatus(const bool completed) const
	{
		m_completedCheck->setCheckState(completed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
		m_todoLineEdit->setFont(completed
			                        ? ThemeManager::instance().strikeFont()
			                        : ThemeManager::instance().itemFont());
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
		m_impCheck->setCheckState(important ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
	}

	// ********************* EDITABLE SUPPORT **********************

	void TodoListItem::setEditable(bool enabled) const // By default, items is set to non-editable.
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
