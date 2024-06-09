#include "DataManager.h"

#include <QFile>
#include <QByteArray>
#include <QJsonValue>

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

QJsonObject Category::toJson() const
{
	QJsonObject jsonObject;
	jsonObject["name"] = name;

	QJsonArray jsonArray;
	for(const auto& item : items)
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
	for(const auto elm : itemsArray)
	{
		TodoItemData item;
		item.fromJson(elm.toObject());
		items.append(item);
	}
}

void DataManager::saveToJson(const QString& filePath)
{
	QFile file(filePath);
	if(!file.open(QIODeviceBase::WriteOnly))
	{
		qWarning() << "Couldn't open the file for write at " << filePath;
		return;
	}

	const QJsonArray jsonArray = categoriesToJson();
	QJsonDocument saveDoc(jsonArray);
	file.write(saveDoc.toJson());
}

void DataManager::loadFromJson(const QString& filePath)
{
	QFile file(filePath);
	if(!file.open(QIODeviceBase::ReadOnly))
	{
		qWarning() << "Couldn't open the file for read at " << filePath;
		return;
	}

	const QByteArray data = file.readAll();
	QJsonDocument loadDoc(QJsonDocument::fromJson(data));

	categories.clear();
	QJsonArray jsonArray = loadDoc.array();
	for(const auto value : jsonArray)
	{
		Category category;
		category.fromJson(value.toObject());
		categories.append(category);
	}


}

QJsonArray DataManager::categoriesToJson() const
{
	QJsonArray jsonArray;
	for(const auto& cat : categories)
	{
		jsonArray.append( cat.toJson());
	}
	return jsonArray;
}
