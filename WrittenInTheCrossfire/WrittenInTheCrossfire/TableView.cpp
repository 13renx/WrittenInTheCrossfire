#include "TableView.h"
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

TableView::TableView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/TableView.PNG")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();

	// Initialize widgets
	dearLabel = Widgets::Labels::createLabel("Dear Mom,", 30, 0, 0);
	letterTextArea = tgui::TextArea::create();
	buttonLayout = tgui::VerticalLayout::create({ 240, 220 });
	cancelButton = tgui::Button::create("CANCEL WRITING");
	sendButton = tgui::Button::create("SEND LETTER");

	dearLabel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea) - 40);
	letterTextArea->setSize(730, 647);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea));
	letterTextArea->setMaximumCharacters(1500);
	//letterTextArea->setVisible(false);
	buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayout->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(buttonLayout), tgui::bindHeight(gui) - tgui::bindHeight(buttonLayout));

	cancelButton->onClick([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});
	sendButton->onClick([=] {
		
	});

	mainPanel->add(dearLabel);
	mainPanel->add(letterTextArea);
	mainPanel->add(buttonLayout);
	buttonLayout->add(cancelButton);
	buttonLayout->add(sendButton);
	gui.add(mainPanel);
}