#include "SettingsView.h"
#include "Widgets.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SettingsView::SettingsView(tgui::Gui& gui, ViewManager* viewManager) : View(viewManager) {
	sf::Window* window = gui.getWindow();

	mainPanel = Widgets::Panels::createPanel("Assets/Textures/Backgrounds/Settings Page with other stuff.png");
	backLabel = Widgets::Labels::createButtonLabel("BACK", 50, 120, 930, window);
	titleLabel = Widgets::Labels::createLabel("SETTINGS", 70, 120, 100);
	
	backLabel->onClick([=, &gui] {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewManager->changeView(ViewManager::ViewType::MENU_VIEW);
	});

	mainPanel->add(backLabel);
	mainPanel->add(titleLabel);
	gui.add(mainPanel);
}

