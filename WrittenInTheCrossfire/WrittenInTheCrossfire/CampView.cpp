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



	gui.add(mainPanel);
}