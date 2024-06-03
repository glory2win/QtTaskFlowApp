#include "TaskFlow.h"

#include <QtWidgets/QApplication>
#include <QString>

#include "ThemeManager.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	TaskFlow flowWindow;

	// TODO: Read the config file see what is current theme and apply that here
	const int themeId = 0; // Dusk = 0, Light = 1, Dark = 2; Read this from config.json file. QtSettings.
	// Note: Dusk uses the default theme that I have designed with Figma.
	ThemeManager themeManager;
	switch (themeId)
	{
	case 0:
		themeManager.applyStyleSheet(app, QString(":/styles/style.css")); // TODO: use dusk_style.css

		break;
	case 1:
		themeManager.applyStyleSheet(app, QString(":/styles/light_style.css"));

		break;
	case 2:
		themeManager.applyStyleSheet(app, QString(":/styles/dark_style.css"));

		break;

	default:
		themeManager.applyStyleSheet(app, QString(":/styles/style.css")); // default one

		break;
	}

	flowWindow.show();
	return app.exec();
}
