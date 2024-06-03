#include "ThemeManager.h"
#include <QApplication>
#include <QString>
#include <QFile>
#include <QMessageBox>

void ThemeManager::applyStyleSheet(QApplication& app, const QString& styleSheetPath)
{
	if(!styleSheetPath.isNull() || !styleSheetPath.isEmpty())
	{
		QFile file(styleSheetPath);
		if(file.open(QFile::ReadOnly))
		{
			QString styleSheet = QLatin1String(file.readAll()); // TODO: select theme file based on selection from setting's combobox.
			app.setStyleSheet(styleSheet);
			file.close();
		}
		else
		{
			qWarning("Could not open stylesheet file.");
			QMessageBox::warning(nullptr, "Error", "Could not load stylesheet " + styleSheetPath);
		}
	}
}
