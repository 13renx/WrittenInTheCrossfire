#include "ViewController.h"
#include "CampView.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "MainMenuView.h"
#include "ReadLetterView.h"
#include "SceneModel.h"
#include "SceneView.h"
#include "SettingsView.h"
#include "AboutView.h"
#include "WriteLetterView.h"
#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ViewController::ViewController(GameModel& gameModel) : gameModel(gameModel), globalWidgets(std::make_shared<GlobalWidgets>(this->gameModel.getWindow(), this->gameModel.getGui(), this)), sceneModel(SceneModel()), activeViewType(ViewController::ViewType::READ_LETTER_VIEW), activeView(std::make_shared<ReadLetterView>(this, this->gameModel)) {}

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
			break;
		case ViewType::SETTINGS_VIEW:
			activeView = std::make_shared<SettingsView>(this, this->gameModel);
			break;
		case ViewType::ABOUT_VIEW:
			activeView = std::make_shared<AboutView>(this, this->gameModel);
			break;
		case ViewType::SCENE_VIEW:
			activeView = std::make_shared<SceneView>(this, this->gameModel, sceneModel);
			break;
		case ViewType::READ_LETTER_VIEW:
			activeView = std::make_shared<ReadLetterView>(this, this->gameModel);
			break;
		case ViewType::CAMP_VIEW:
			activeView = std::make_shared<CampView>(this, this->gameModel);
			break;
		case ViewType::WRITE_LETTER_VIEW:
			activeView = std::make_shared<WriteLetterView>(this, this->gameModel);
			break;
	}
}