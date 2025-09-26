#include "ViewManager.h"
#include "CampView.h"
#include "Client.h"
#include "MenuView.h"
#include "SettingsView.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ViewManager::ViewManager(tgui::Gui& gui) : client(Client()), gui(gui), activeView(std::make_shared<MenuView>(client, gui, this)) {}

std::shared_ptr<View> ViewManager::getActiveView() {
	return activeView;
}

void ViewManager::setActiveView(std::shared_ptr<View> view) {
	activeView = view;
}

void ViewManager::changeView(ViewType viewType) {
	gui.removeAllWidgets();

	switch(viewType) {
		case ViewType::MENU_VIEW:
			setActiveView(std::make_shared<MenuView>(client, gui, this));
			break;
		case ViewType::SETTINGS_VIEW:
			setActiveView(std::make_shared<SettingsView>(gui, this));
			break;
		case ViewType::CAMP_VIEW:
			setActiveView(std::make_shared<CampView>(client, gui, this));
			break;
	}
}