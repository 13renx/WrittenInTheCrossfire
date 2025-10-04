#include "ViewController.h"
#include "CampView.h"
#include "GameModel.h"
#include "MenuView.h"
#include "SettingsView.h"
#include "AboutView.h"
#include "TableView.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ViewController::ViewController(GameModel& gameModel) : gameModel(gameModel), activeView(std::make_shared<MenuView>(this, this->gameModel)) {}

std::shared_ptr<View> ViewController::getActiveView() {
	return activeView;
}

void ViewController::setActiveView(std::shared_ptr<View> view) {
	activeView = view;
}

void ViewController::changeView(ViewType viewType) {
	this->gameModel.getGui().removeAllWidgets();

	switch(viewType) {
		case ViewType::MENU_VIEW:
			setActiveView(std::make_shared<MenuView>(this, this->gameModel));
			break;
		case ViewType::SETTINGS_VIEW:
			setActiveView(std::make_shared<SettingsView>(this, this->gameModel));
			break;
		case ViewType::ABOUT_VIEW:
			setActiveView(std::make_shared<AboutView>(this, this->gameModel));
			break;
		case ViewType::CAMP_VIEW:
			setActiveView(std::make_shared<CampView>(this, this->gameModel));
			break;
		case ViewType::TABLE_VIEW:
			setActiveView(std::make_shared<TableView>(this, this->gameModel));
			break;
	}
}