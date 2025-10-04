#include "AboutView.h"
#include "GameModel.h"
#include "Widgets.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

AboutView::AboutView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/Settings Page with other stuff.png")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();

	// Initialize widgets
	titleLabel = Widgets::Labels::createLabel("ABOUT", 100, 700, 70);
	leftLayout = tgui::GrowVerticalLayout::create(1000);
	backLabel = Widgets::Labels::createButtonLabel("BACK", 50, 0, 0, window);
	buttonsLayout = tgui::GrowHorizontalLayout::create();

	leftLayout->setPosition(120, 200);
	buttonsLayout->setPosition(120, 930);
	buttonsLayout->getRenderer()->setSpaceBetweenWidgets(20);

	backLabel->onClick([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::MENU_VIEW);
		});

	mainPanel->add(titleLabel);
	mainPanel->add(leftLayout);
	mainPanel->add(buttonsLayout);
	buttonsLayout->add(backLabel);
	gui.add(mainPanel);
}