#include "AboutView.h"
#include "GameModel.h"
#include "Macros.h"
#include "Utils.h"
#include "Widgets.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

AboutView::AboutView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("./Assets/Textures/Backgrounds/Bulletin Board.png")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().playMusic();

	// Initialize widgets
	titleLabel = Widgets::Labels::createLabel("ABOUT", 100, 700, 70);
	textLabel = Widgets::Labels::createLabel("Written In the Crossfire follows the narrative of a soldier during war, writing letters to home,", 30, 0, 0);
	textLabel2 = Widgets::Labels::createLabel("and uncovering the human cost of conflict.", 30, 0, 0);
	textLabel3 = Widgets::Labels::createLabel("Created by Angela Miguel, Joaquin Panganiban, Brent Soan, Ana Veron", 30, 0, 0);
	leftLayout = tgui::GrowVerticalLayout::create(1500);
	spacer = tgui::Label::create();
	backLabel = Widgets::Labels::createButtonLabel("BACK", 50, 0, 0, window);
	buttonsLayout = tgui::GrowHorizontalLayout::create();

	leftLayout->setPosition(120, 200);
	buttonsLayout->setPosition(120, 930);
	spacer->setHeight(500);

	backLabel->onClick([=, &window] {
		Utils::Log::debugInfo("backLabel clicked");

		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
	});

	mainPanel->add(titleLabel);
	mainPanel->add(leftLayout);
	leftLayout->add(textLabel);
	leftLayout->add(textLabel2);
	leftLayout->add(spacer);
	leftLayout->add(textLabel3);
	mainPanel->add(buttonsLayout);
	buttonsLayout->add(backLabel);
}