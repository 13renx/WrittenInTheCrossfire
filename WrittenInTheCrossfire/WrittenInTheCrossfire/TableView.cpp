#include "TableView.h"
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

TableView::TableView(Client& client, tgui::Gui& gui, ViewManager* viewManager) : View(gui, viewManager, tgui::Color::Black), client(client) {
	gameModel = GameModel();

	dearLabel = Widgets::Labels::createLabel("Dear Mom,", 30, 0, 0);
	letterTextArea = tgui::TextArea::create();
	buttonLayout = tgui::VerticalLayout::create({ 300, 200 });
	cancelButton = tgui::Button::create("CANCEL WRITING");
	sendButton = tgui::Button::create("SEND LETTER");

	letterTextArea->setSize(800, 300);
	letterTextArea->setTextSize(30);
	//letterTextArea->setVisible(false);
	buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);

	mainPanel->add(letterTextArea);
	mainPanel->add(buttonLayout);
	buttonLayout->add(cancelButton);
	buttonLayout->add(sendButton);
	gui.add(mainPanel);
}