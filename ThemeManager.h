#pragma once

// Reads stylesheets
class QApplication;
class QString;

class ThemeManager
{
public:
	ThemeManager() = default;

	void applyStyleSheet(QApplication& app, const QString& styleSheetPath);
};

