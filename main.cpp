// #define USE_TEST_WIDGET

#include <QtWidgets/QApplication>

#ifdef USE_TEST_WIDGET
#include "views/TestWidgetView.h"
#else
#include "views/TaskFlowView.h"

#endif

#include "utilities/ThemeManager.h"
#include "models/DataManager.h"
#include "presenters/TaskFlowPresenter.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

#ifdef USE_TEST_WIDGET
	Tests::TestWidget testWidget;
	testWidget.show();

#else
	/* Load and Save application data to Json, assuming ./data/data.json */
	Model::DataManager dataManager;
	View::TaskFlowView flowWindow;
	Presenter::TaskFlowPresenter controller(&dataManager, &flowWindow);

	dataManager.loadFromJson(DataManager::dataFilePath);
	QString debugStr = dataManager.toString();
	qDebug() << "data: " << debugStr;


	ThemeManager::instance().loadTheme(app);

	flowWindow.setFixedSize(1024, 768);
	flowWindow.show();

#endif

	return app.exec();
}
