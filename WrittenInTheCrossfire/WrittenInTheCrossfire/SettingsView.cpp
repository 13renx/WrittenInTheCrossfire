#include "SettingsView.h"

SettingsView::SettingsView(tgui::Gui& g, std::shared_ptr<View> v) : View(g, v) {
	titleLabel = tgui::Label::create("SETTINGS");
	titleLabel->setPosition(100, 100);
	titleLabel->setTextSize(70);
	panel->add(titleLabel);
	gui.add(panel);
}