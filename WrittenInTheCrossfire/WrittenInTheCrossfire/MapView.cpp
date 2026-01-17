#include "MapView.h"
#include "Utils.h"
#include "ViewController.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MapView::MapView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("")) {
	tgui::Gui& gui = this->gameModel.getGui();
	
	// Initialize widgets
	backButton = tgui::Button::create("BACK");

	backButton->setSize(240, 100);
	backButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(backButton), tgui::bindHeight(gui) - tgui::bindHeight(backButton));

	backButton->onClick([=] {
		Utils::Log::info("backButton clicked");

		backButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});

	mainPanel->add(backButton);
}