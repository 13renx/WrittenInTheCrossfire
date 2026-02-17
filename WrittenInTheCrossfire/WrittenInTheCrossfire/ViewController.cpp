#include "ViewController.h"
#include "CampView.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "MainMenuView.h"
#include "MapView.h"
#include "ReadLetterView.h"
#include "StoryModel.h"
#include "Structs.h"
#include "MainSceneView.h"
#include "SettingsView.h"
#include "Utils.h"
#include "AboutView.h"
#include "WriteLetterView.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ViewController::ViewController(GameModel& gameModel) : gameModel(gameModel), globalWidgets(std::make_shared<GlobalWidgets>(this->gameModel.getWindow(), this->gameModel.getGui(), this)), storyModel(StoryModel()), activeViewType(ViewController::ViewType::MAIN_MENU_VIEW), activeView(std::make_shared<MainMenuView>(this, this->gameModel)) {}

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
			Utils::Log::debugInfo("activeView updated to MainMenuView");
			break;
		case ViewType::SETTINGS_VIEW:
			activeView = std::make_shared<SettingsView>(this, this->gameModel);
			Utils::Log::debugInfo("activeView updated to SettingsView");
			break;
		case ViewType::ABOUT_VIEW:
			activeView = std::make_shared<AboutView>(this, this->gameModel);
			Utils::Log::debugInfo("activeView updated to AboutView");
			break;
		case ViewType::MAIN_SCENE_VIEW:
			activeView = std::make_shared<MainSceneView>(this, this->gameModel, this->storyModel);
			Utils::Log::debugInfo("activeView updated to MainSceneView");
			break;
		case ViewType::READ_LETTER_VIEW:
			activeView = std::make_shared<ReadLetterView>(this, this->gameModel);
			Utils::Log::debugInfo("activeView updated to ReadLetterView");
			break;
		case ViewType::CAMP_VIEW:
			activeView = std::make_shared<CampView>(this, this->gameModel, this->storyModel);
			Utils::Log::debugInfo("activeView updated to CampView");
			break;
		case ViewType::WRITE_LETTER_VIEW:
			activeView = std::make_shared<WriteLetterView>(this, this->gameModel);
			Utils::Log::debugInfo("activeView updated to WriteLetterView");
			break;
		case ViewType::MAP_VIEW:
			activeView = std::make_shared<MapView>(this, this->gameModel);
			Utils::Log::debugInfo("activeView updated to MapView");
			break;
	}
}