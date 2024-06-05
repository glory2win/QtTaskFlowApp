#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

/* QLineEdit needs to be extended inorder to call the focusOutEvent. */
class CategoryLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	explicit CategoryLineEdit(QWidget* parent);
	~CategoryLineEdit() override = default;

protected:
	void focusOutEvent(QFocusEvent* event) override;

private:
	signals:
		void focusChanged();
};

class CategoryListItem : public QWidget
{
	Q_OBJECT

public:
	explicit CategoryListItem(QWidget* parent);
	~CategoryListItem() override = default;

	void setCategoryName(const QString& rename) const;
	void setEditable(bool enabled) const;

private	slots:
		auto handleLostFocus() -> void;

private:

	QLabel* m_iconLabel;
	CategoryLineEdit* m_categoryLineEdit;
};
