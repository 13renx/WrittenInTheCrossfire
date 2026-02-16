#include "MapView.h"
#include "Utils.h"
#include "ViewController.h"
#include "Widgets.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MapView::MapView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("./Assets/Textures/Backgrounds/MapView.PNG")) {
	tgui::Gui& gui = this->gameModel.getGui();
	sf::RenderWindow& window = this->gameModel.getWindow();

	// Initialize widgets
	bunkerPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("./Assets/Textures/Interactables/Map Locations/Bunker.PNG"));
	mealAreaPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("./Assets/Textures/Interactables/Map Locations/Meal Time Morning.PNG"));
	storageBunkerPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("./Assets/Textures/Interactables/Map Locations/Storage Bunker.PNG"));
	backButton = tgui::Button::create("BACK");

	bunkerPicture->setPosition(100, 200);
	mealAreaPicture->setPosition(650, 300);
	storageBunkerPicture->setPosition(1200, 250);
	backButton->setSize(240, 100);
	backButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(backButton), tgui::bindHeight(gui) - tgui::bindHeight(backButton));

	backButton->onClick([=] {
		Utils::Log::info("backButton clicked");

		backButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});
	bunkerPicture->onClick([=] {
		Utils::Log::info("bunkerPicture clicked");
	});
	mealAreaPicture->onClick([=] {
		Utils::Log::info("mealAreaPicture clicked");
	});
	storageBunkerPicture->onClick([=] {
		Utils::Log::info("storageBunkerPicture clicked");
	});

	mainPanel->add(bunkerPicture);
	mainPanel->add(mealAreaPicture);
	mainPanel->add(storageBunkerPicture);
	mainPanel->add(backButton);
}