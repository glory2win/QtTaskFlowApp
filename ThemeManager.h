#pragma once

// Reads stylesheets
class QApplication;
class QString;
class QFont;

enum class ETheme
{
	Dusk,
	Dark,
	Light
};

class ThemeManager
{
public:
	ThemeManager();
	~ThemeManager();

	static QFont& titleFont() { return *s_instance->m_titleFont; }
	static QFont& itemFont() { return *s_instance->m_itemFont; }

	void loadTheme(QApplication& app);

private:

	static void applyStyleSheet(QApplication& app, const QString& styleSheetPath);

private:

	static ThemeManager* s_instance;

	QFont* m_titleFont;
	QFont* m_itemFont;
};

