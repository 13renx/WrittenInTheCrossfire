#include "ViewController.h"
#include "CampView.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "MainMenuView.h"
#include "MapView.h"
#include "ReadLetterView.h"
#include "SceneModel.h"
#include "SceneView.h"
#include "SettingsView.h"
#include "Utils.h"
#include "AboutView.h"
#include "WriteLetterView.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ViewController::ViewController(GameModel& gameModel) : gameModel(gameModel), globalWidgets(std::make_shared<GlobalWidgets>(this->gameModel.getWindow(), this->gameModel.getGui(), this)), sceneModel(SceneModel()), activeViewType(ViewController::ViewType::CAMP_VIEW), activeView(std::make_shared<CampView>(this, this->gameModel)) {}

std::shared_ptr<GlobalWidgets> ViewController::getGlobalWidgets() {
	return globalWidgets;
}

ViewController::ViewType& ViewController::getActiveViewType() {
	return activeViewType;
}

void ViewController::changeView(ViewType viewType) {
	activeViewType = viewType;
	this->globalWidgets->getMainPanel()->removeAllWidgets();

	switch(activeViewType) {
		case ViewType::MAIN_MENU_VIEW:
			activeView = std::make_shared<MainMenuView>(this, this->gameModel);
			Utils::Log::info("activeView updated to MainMenuView");
			break;
		case ViewType::SETTINGS_VIEW:
			activeView = std::make_shared<SettingsView>(this, this->gameModel);
			Utils::Log::info("activeView updated to SettingsView");
			break;
		case ViewType::ABOUT_VIEW:
			activeView = std::make_shared<AboutView>(this, this->gameModel);
			Utils::Log::info("activeView updated to AboutView");
			break;
		case ViewType::SCENE_VIEW:
			activeView = std::make_shared<SceneView>(this, this->gameModel, sceneModel);
			Utils::Log::info("activeView updated to SceneView");
			break;
		case ViewType::READ_LETTER_VIEW:
			activeView = std::make_shared<ReadLetterView>(this, this->gameModel);
			Utils::Log::info("activeView updated to ReadLetterView");
			break;
		case ViewType::CAMP_VIEW:
			activeView = std::make_shared<CampView>(this, this->gameModel);
			Utils::Log::info("activeView updated to CampView");
			break;
		case ViewType::WRITE_LETTER_VIEW:
			activeView = std::make_shared<WriteLetterView>(this, this->gameModel);
			Utils::Log::info("activeView updated to WriteLetterView");
			break;
		case ViewType::MAP_VIEW:
			activeView = std::make_shared<MapView>(this, this->gameModel);
			Utils::Log::info("activeView updated to MapView");
			break;
	}
}