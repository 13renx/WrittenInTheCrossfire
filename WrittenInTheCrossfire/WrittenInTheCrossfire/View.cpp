#include "View.h"
#include "GameModel.h"
#include "ViewController.h"
#include "Widgets.h"
#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

View::View(ViewController* viewController, GameModel& gameModel, tgui::Texture mainPanelTexture) : viewController(viewController), gameModel(gameModel) {
	mainPanel = Widgets::Panels::createPanel(mainPanelTexture);
	init();
}

View::View(ViewController* viewController, GameModel& gameModel, tgui::Color mainPanelColor) : viewController(viewController), gameModel(gameModel) {
	mainPanel = Widgets::Panels::createPanel(mainPanelColor);
	init();
}

void View::init() {
	alertChildWindow = tgui::ChildWindow::create();
	alertLabel = Widgets::Labels::createLabel("", 13, 0, 0);

	alertChildWindow->setSize(400, 100);
	alertChildWindow->setCloseBehavior(tgui::ChildWindow::CloseBehavior::Hide);
	alertChildWindow->setPositionLocked(true);
	alertChildWindow->setPosition((tgui::bindWidth(this->gameModel.getGui()) - tgui::bindWidth(alertChildWindow)) / 2.0f, 0);
	alertChildWindow->setVisible(false);
	alertLabel->setPosition(10, 10);
}