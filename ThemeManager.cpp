#include "ThemeManager.h"
#include <QApplication>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QFontDatabase>

ThemeManager* ThemeManager::s_instance = nullptr;

ThemeManager::ThemeManager()
{
	// IMP: When setting up the font with "Arial" kind of notation in QFont will query the font from the computer not from resources
	// In case of custom font, we have to load that first and then create QFont from that. To do that use QFontDatabase class
	if (const int fontId = QFontDatabase::addApplicationFont(":/fonts/Itim-Regular.ttf"); fontId != -1)
	// -1 mean no failure to load the font
	{
		QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
		if (!fontFamilies.empty())
		{
			const QString& fontName = fontFamilies.at(0); // Get the first one.

			m_titleFont = new QFont(fontName, 28);
			m_itemFont = new QFont(fontName, 12);
		}
		else
		{
			qWarning("[Font] - Font family is empty");
		}
	}
	else
	{
		qWarning("Unable to get the font!");
	}

	s_instance = this;

	qDebug() << "Theme Manager has created";
}

ThemeManager::~ThemeManager()
{
	qDebug() << "Theme Manager has destroyed";
	s_instance = nullptr;
	delete m_titleFont;
	delete m_itemFont;
	// delete s_instance; // NOTE: Don't delete s_instance which causes running destructor again which causes font are not related error. This ~ThemeManager called from main.
}

void ThemeManager::applyStyleSheet(QApplication& app, const QString& styleSheetPath)
{
	if (!styleSheetPath.isNull() || !styleSheetPath.isEmpty())
	{
		QFile file(styleSheetPath);
		if (file.open(QFile::ReadOnly))
		{
			QString styleSheet = QLatin1String(file.readAll());
			// TODO: select theme file based on selection from setting's combobox.
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


void ThemeManager::loadTheme(QApplication& app)
{
	// TODO: Read the config file see what is current theme and apply that here
	const int themeId = 0; // Dusk = 0, Light = 1, Dark = 2; Read this from config.json file. QtSettings.
	// Note: Dusk uses the default theme that I have designed with Figma.
	switch (themeId)
	{
	case 0:
		applyStyleSheet(app, QString(":/styles/style.css")); // TODO: use dusk_style.css

		break;
	case 1:
		applyStyleSheet(app, QString(":/styles/light_style.css"));

		break;
	case 2:
		applyStyleSheet(app, QString(":/styles/dark_style.css"));

		break;

	default:
		applyStyleSheet(app, QString(":/styles/style.css")); // default one

		break;
	}
}
