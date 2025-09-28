#include "CampView.h"
#include "Client.h"
#include "Macros.h"
#include "View.h"
#include "ViewManager.h"
#include "Widgets.h"
#include <fstream>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

CampView::CampView(Client& client, tgui::Gui& gui, ViewManager* viewManager) : View(gui, viewManager, tgui::Texture::Texture("Assets/Textures/Backgrounds/full_body_bg.PNG")), client(client) {
	gameModel = GameModel();

    buttonLayoutOne = tgui::HorizontalLayout::create({ 200, 300 });
    writeButton = tgui::Button::create("WRITE A LETTER");
	dontWriteButton = tgui::Button::create("DON'T WRITE A LETTER");
	buttonLayoutTwo = tgui::VerticalLayout::create({ 300, 200 });
    cancelButton = tgui::Button::create("CANCEL");
	selectButton = tgui::Button::create("SELECT");
	
    buttonLayoutOne->getRenderer()->setSpaceBetweenWidgets(20);
    buttonLayoutTwo->getRenderer()->setSpaceBetweenWidgets(20);
    buttonLayoutTwo->setVisible(false);

	mainPanel->add(buttonLayoutOne);
	mainPanel->add(buttonLayoutTwo);
	buttonLayoutOne->add(writeButton);
	buttonLayoutOne->add(dontWriteButton);
	buttonLayoutTwo->add(cancelButton);
	buttonLayoutTwo->add(selectButton);
	gui.add(mainPanel);
}