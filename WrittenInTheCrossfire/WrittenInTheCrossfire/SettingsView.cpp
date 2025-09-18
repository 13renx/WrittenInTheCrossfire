#include "SettingsView.h"
#include "Widgets.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SettingsView::SettingsView(tgui::Gui& g, std::shared_ptr<View> v) : View(g, v) {
	sf::Window* window = g.getWindow();

	mainPanel = Widgets::Panels::createPanel("Assets/Textures/Backgrounds/Settings Page with other stuff.png");
	titleLabel = Widgets::Labels::createLabel("Settings", 70, 100, 100);

	mainPanel->add(titleLabel);
	gui.add(mainPanel);
}