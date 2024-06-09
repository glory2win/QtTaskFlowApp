// #define USE_TEST_WIDGET

#include <QtWidgets/QApplication>

#ifdef USE_TEST_WIDGET
#include "TestWidget.h"
#else
#include "TaskFlow.h"
#endif

#include "ThemeManager.h"
#include "DataManager.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

#ifdef USE_TEST_WIDGET
	TestWidget testWidget;
	testWidget.show();

#else
	/* Load and Save application data to Json, assuming ./data/data.json */
	DataManager dataManager;


	ThemeManager::instance().loadTheme(app);

	TaskFlow flowWindow;
	flowWindow.setFixedSize(1024, 768);
	flowWindow.show();

#endif

	return app.exec();
}
