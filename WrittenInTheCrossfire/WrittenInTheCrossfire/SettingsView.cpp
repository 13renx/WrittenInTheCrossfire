#include "SettingsView.h"
#include "Widgets.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SettingsView::SettingsView(tgui::Gui& g, std::shared_ptr<View> v) : View(g, v) {
	mainPanel = Widgets::Panel::createNormalPanel("Assets/Textures/Backgrounds/Settings Page with other stuff.png");
	titleLabel = Widgets::Label::createNormalLabel("Settings", 70, 100, 100);

	mainPanel->add(titleLabel);
	gui.add(mainPanel);
}