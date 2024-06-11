#pragma once

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>

namespace Model
{
	class TodoItemData
	{
	public:
		QString todo;
		bool isCompleted;
		bool isImportant;

		QJsonObject toJson() const;
		void fromJson(const QJsonObject& json);

		QString toString() const;
	};

	class Category
	{
	public:
		QString name;
		QList<TodoItemData> items;
		bool isSelected;

		QJsonObject toJson() const;
		void fromJson(const QJsonObject& json);

		QString toString() const;
	};

	class DataManager : public QObject
	{
		Q_OBJECT
		// read file and fill to data objects during load, read the data objects and write to file when save.
	public:
		explicit DataManager(QObject* parent = nullptr);
		~DataManager() override = default;
		QList<Category> categories;

		void saveToJson(const QString& filePath);
		void loadFromJson(const QString& filePath);

		QString toString() const;


	signals:
		void dataChanged();

	private:
		QJsonArray categoriesToJson() const;
	};
}
