#include "CampView.h"
#include "Client.h"
#include "GameModel.h"
#include "Macros.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

CampView::CampView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/CampView.PNG")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();

	// Initialize widgets
    buttonLayoutOne = tgui::HorizontalLayout::create({ 500, 100 });
    writeButton = tgui::Button::create("WRITE A LETTER");
	dontWriteButton = tgui::Button::create("DON'T WRITE A LETTER");
	buttonLayoutTwo = tgui::VerticalLayout::create({ 240, 220 });
    cancelButton = tgui::Button::create("CANCEL");
	selectButton = tgui::Button::create("SELECT");
	
    buttonLayoutOne->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayoutOne->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(buttonLayoutOne) + 20) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(buttonLayoutOne)) / 2.0f);
    buttonLayoutTwo->getRenderer()->setSpaceBetweenWidgets(20);
    buttonLayoutTwo->setVisible(false);

	writeButton->onClick([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::TABLE_VIEW);
	});

	mainPanel->add(buttonLayoutOne);
	mainPanel->add(buttonLayoutTwo);
	buttonLayoutOne->add(writeButton);
	buttonLayoutOne->add(dontWriteButton);
	buttonLayoutTwo->add(cancelButton);
	buttonLayoutTwo->add(selectButton);
}