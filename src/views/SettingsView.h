#pragma once

#include <QDialog>
#include "ui_Settings.h"

class SettingsView : public QDialog
{
public:
	explicit SettingsView(QWidget* parent = nullptr);
	~SettingsView() override = default;

private:
};

