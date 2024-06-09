#pragma once

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

class TodoItemData
{
public:
	QString todo;
	bool isCompleted;
	bool isImportant;

	QJsonObject toJson() const;
	void fromJson(const QJsonObject& json);
};

class Category
{
public:
	QString name;
	QList<TodoItemData> items;
	bool isSelected;

	QJsonObject toJson() const;
	void fromJson(const QJsonObject& json);
};

class DataManager : QObject
{
	Q_OBJECT
	// read file and fill to data objects during load, read the data objects and write to file when save.
public:
	QList<Category> categories;

	void saveToJson(const QString& filePath);
	void loadFromJson(const QString& filePath);

signals:
	void dataChanged();

private:
	QJsonArray categoriesToJson() const;
};
