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

	QFont& titleFont() { return *m_titleFont; }
	QFont& itemFont() const { return *m_itemFont; }
	QFont& strikeFont() const { return *m_strikeFont; }

	void loadTheme(QApplication& app);

private:
	// private ctor and dtor due to singleton can create class
	ThemeManager();
	~ThemeManager();

	static void applyStyleSheet(QApplication& app, const QString& styleSheetPath);

private:

	std::unique_ptr<QFont> m_titleFont;
	std::unique_ptr<QFont> m_itemFont; // TODO: assign different font for todo list item.
	std::unique_ptr<QFont> m_strikeFont; // Qt's text-decoration in css is limited so need to create a new font for this.
};

