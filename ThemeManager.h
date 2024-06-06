#pragma once

#include <memory>

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

	ThemeManager(const ThemeManager&) = delete;
	ThemeManager& operator=(const ThemeManager&) = delete;

	static ThemeManager& instance();

	QFont& titleFont() const { return *m_titleFont; }
	QFont& itemFont() const { return *m_itemFont; }

	void loadTheme(QApplication& app);

private:
	// private ctor and dtor due to singleton can create class
	ThemeManager();
	~ThemeManager();

	static void applyStyleSheet(QApplication& app, const QString& styleSheetPath);

private:

	std::unique_ptr<QFont> m_titleFont;
	std::unique_ptr<QFont> m_itemFont;
};

