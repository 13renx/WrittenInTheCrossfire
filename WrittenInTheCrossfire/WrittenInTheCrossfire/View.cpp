#include "View.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "ViewController.h"
#include "Widgets.h"
#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

View::View(ViewController* viewController, GameModel& gameModel, tgui::Texture mainPanelTexture) : viewController(viewController), gameModel(gameModel) {
	std::shared_ptr<GlobalWidgets> globalWidgets = this->viewController->getGlobalWidgets();

	mainPanel = globalWidgets->getMainPanel();
	alertChildWindow = globalWidgets->getAlertChildWindow();
	alertLabel = globalWidgets->getAlertLabel();

	mainPanel->getRenderer()->setTextureBackground(mainPanelTexture);
}