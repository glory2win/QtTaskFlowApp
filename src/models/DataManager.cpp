#include "DataManager.h"

#include <QFile>
#include <QByteArray>
#include <QJsonValue>
#include <sstream>

namespace Model
{
	namespace Data
	{
		// ************* TO DO ITEM DATA *******************

		QJsonObject TodoItemData::toJson() const
		{
			QJsonObject json;
			json["todo"] = todo;
			json["done"] = isCompleted;
			json["imp"] = isImportant;

			return json;
		}

		void TodoItemData::fromJson(const QJsonObject& json)
		{
			todo = json["todo"].toString("No Work");
			isCompleted = json["done"].toBool(false);
			isImportant = json["imp"].toBool(false);
		}

		QString TodoItemData::toString() const
		{
			QString result;
			result += todo + "\n completed: " + (isCompleted ? QLatin1String("true") : QLatin1String("false"));
			return result;
		}

		// ************* CATEGORY ITEM DATA *******************

		QJsonObject Category::toJson() const
		{
			QJsonObject jsonObject;
			jsonObject["name"] = name;

			QJsonArray jsonArray;
			for (const auto& item : items)
			{
				jsonArray.append(item.toJson());
			}

			jsonObject["items"] = jsonArray;

			jsonObject["selected"] = isSelected;

			return jsonObject;
		}

		void Category::fromJson(const QJsonObject& json)
		{
			name = json.value("name").toString("Untitled");
			isSelected = json.value("selected").toBool(false);

			QJsonArray itemsArray = json.value("items").toArray({});
			items.clear();
			for (const auto elm : itemsArray)
			{
				TodoItemData item;
				item.fromJson(elm.toObject());
				items.append(item);
			}
		}

		QString Category::toString() const
		{
			QString result;
			result += name + "\n";
			for (const auto& elm : items)
			{
				result += "\t" + elm.toString();
			}
			return result;
		}
	}

	// ************* DATA MANAGER *******************

	DataManager::DataManager(QObject* parent) : QObject(parent)
	{
	}

	void DataManager::saveToJson(const QString& filePath)
	{
		if (!QFile::exists(filePath))
		{
			qWarning() << "File not found at " << filePath;
			return;
		}

		QFile file(filePath);
		if (!file.open(QIODeviceBase::WriteOnly))
		{
			qWarning() << "Couldn't open the file for write at " << filePath;
			return;
		}

		const QJsonArray jsonArray = categoriesToJson();
		QJsonDocument saveDoc(jsonArray);
		file.write(saveDoc.toJson());

		// emit dataChanged();
	}

	void DataManager::loadFromJson(const QString& filePath)
	{
		if (!QFile::exists(filePath))
		{
			qWarning() << "File not found at " << filePath;
			return;
		}

		QFile file(filePath);

		if (!file.open(QIODeviceBase::ReadOnly))
		{
			qWarning() << "Couldn't open the file for read at " << filePath;
			return;
		}

		const QByteArray data = file.readAll();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
		if (!jsonDoc.isNull() && jsonDoc.isObject())
		{
			const QJsonObject& jsonObj = jsonDoc.object();
			const QJsonValue& jsonValue = jsonObj.value("categories");
			const QJsonArray& jsonArray = jsonValue.toArray();
			categories.clear();
			for (const auto elm : jsonArray)
			{
				Data::Category category;
				category.fromJson(elm.toObject());
				categories.append(category);
			}
			emit dataChanged();
		}
		else
		{
			qWarning() << "Unable to read the JSON document, it may be null or not an object!";
		}
	}

	QString DataManager::toString() const
	{
		QString result;
		result += "{\n";
		for (const auto& category : categories)
		{
			result += category.toString();
			result += "\n\n";
		}
		result += "\n}";

		return result;
	}

	void DataManager::onDataSaved()
	{
		saveToJson("data/sample.json");
		qDebug() << "Json file has been updated at: data/sample.json" << __FUNCTION__;
	}

	QJsonArray DataManager::categoriesToJson() const
	{
		QJsonArray jsonArray;
		for (const auto& cat : categories)
		{
			jsonArray.append(cat.toJson());
		}
		return jsonArray;
	}
}
