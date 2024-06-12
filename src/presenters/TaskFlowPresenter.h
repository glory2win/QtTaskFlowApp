#pragma once

#include <models/DataManager.h>
#include <views/TaskFlowView.h>

using namespace Model;
using namespace View;

namespace Presenter
{
	class TaskFlowPresenter : public QObject
	{
		Q_OBJECT

	public:
		explicit TaskFlowPresenter(DataManager* model, TaskFlowView* view, QObject* parent = nullptr);

		~TaskFlowPresenter() override = default;

	private slots:
		//View
		void onNewCategoryAdded(const QString& name);
		void onCategorySelected(const CategoryListItem* category);
		void onCategoryNameChanged(const QString& rename);
		// Model
		void onDataLoaded();

	private:
		DataManager* m_model;
		TaskFlowView* m_view;

		Data::Category* m_currCategoryData;
	};
}
