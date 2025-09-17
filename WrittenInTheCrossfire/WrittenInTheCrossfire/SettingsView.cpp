#include "SettingsView.h"

SettingsView::SettingsView(tgui::Gui& g, std::shared_ptr<View> v) : View(g, v) {
	mainPanel = tgui::Panel::create();
	titleLabel = tgui::Label::create("SETTINGS");

	mainPanel->getRenderer()->setTextureBackground("Assets/Textures/Backgrounds/Settings Page with other stuff.png");
	titleLabel->setPosition(100, 100);
	titleLabel->setTextSize(70);

	mainPanel->add(titleLabel);
	gui.add(mainPanel);
}