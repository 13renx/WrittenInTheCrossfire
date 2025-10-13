#include "ViewController.h"
#include "CampView.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "MainMenuView.h"
#include "SceneView.h"
#include "SettingsView.h"
#include "AboutView.h"
#include "TableView.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ViewController::ViewController(GameModel& gameModel) : gameModel(gameModel), globalWidgets(std::make_shared<GlobalWidgets>(this->gameModel.getWindow(), this->gameModel.getGui(), this)), activeView(std::make_shared<TableView>(this, this->gameModel)), activeViewType(ViewController::ViewType::TABLE_VIEW) {}

std::shared_ptr<GlobalWidgets> ViewController::getGlobalWidgets() {
	return globalWidgets;
}

std::shared_ptr<View> ViewController::getActiveView() {
	return activeView;
}

ViewController::ViewType& ViewController::getActiveViewType() {
	return activeViewType;
}

void ViewController::setActiveView(std::shared_ptr<View> view) {
	activeView = view;
}

void ViewController::setActiveViewType(ViewType viewType) {
	activeViewType = viewType;
}

void ViewController::changeView(ViewType viewType) {
	activeViewType = viewType;
	this->globalWidgets->getMainPanel()->removeAllWidgets();

	switch(activeViewType) {
		case ViewType::MAIN_MENU_VIEW:
			setActiveView(std::make_shared<MainMenuView>(this, this->gameModel));
			break;
		case ViewType::SETTINGS_VIEW:
			setActiveView(std::make_shared<SettingsView>(this, this->gameModel));
			break;
		case ViewType::ABOUT_VIEW:
			setActiveView(std::make_shared<AboutView>(this, this->gameModel));
			break;
		case ViewType::SCENE_VIEW:
			setActiveView(std::make_shared<SceneView>(this, this->gameModel));
			break;
		case ViewType::CAMP_VIEW:
			setActiveView(std::make_shared<CampView>(this, this->gameModel));
			break;
		case ViewType::TABLE_VIEW:
			setActiveView(std::make_shared<TableView>(this, this->gameModel));
			break;
	}
}