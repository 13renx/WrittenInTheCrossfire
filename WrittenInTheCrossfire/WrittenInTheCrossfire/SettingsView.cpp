#include "SettingsView.h"
#include "Widgets.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SettingsView::SettingsView(tgui::Gui& gui, std::shared_ptr<View> activeView) : View(activeView) {
	sf::Window* window = gui.getWindow();

	mainPanel = Widgets::Panels::createPanel("Assets/Textures/Backgrounds/Settings Page with other stuff.png");
	titleLabel = Widgets::Labels::createLabel("Settings", 70, 100, 100);

	mainPanel->add(titleLabel);
	gui.add(mainPanel);
}

