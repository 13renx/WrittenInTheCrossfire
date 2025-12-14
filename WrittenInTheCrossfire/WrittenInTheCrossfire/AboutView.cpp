#include "AboutView.h"
#include "GameModel.h"
#include "Widgets.h"
#include "View.h"
#include "ViewController.h"
#include "Macros.h"
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

AboutView::AboutView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/Settings Page with other stuff.png")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().playMusic();

	// Initialize widgets
	titleLabel = Widgets::Labels::createLabel("ABOUT", 100, 700, 70, Macros::Fonts::Default());
	textLabel = Widgets::Labels::createLabel("Written In the Crossfire follows the narrative of a soldier during war, writing letters to home,", 30, 0, 0, Macros::Fonts::Default());
	textLabel2 = Widgets::Labels::createLabel("and uncovering the human cost of conflict.", 30, 0, 0, Macros::Fonts::Default());
	textLabel3 = Widgets::Labels::createLabel("Created by Angela Miguel, Joaquin Panganiban, Brent Soan, Ana Veron", 30, 0, 0, Macros::Fonts::Default());
	leftLayout = tgui::GrowVerticalLayout::create(1500);
	spacer = tgui::Label::create();
	spacer->setHeight(500);
	backLabel = Widgets::Labels::createButtonLabel("BACK", 50, 0, 0, window, Macros::Fonts::Default());
	buttonsLayout = tgui::GrowHorizontalLayout::create();

	leftLayout->setPosition(120, 200);
	buttonsLayout->setPosition(120, 930);

	backLabel->onClick([=, &window] {
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