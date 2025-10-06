#include "SceneView.h"
#include "Client.h"
#include "Macros.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SceneView::SceneView(Client& client, tgui::Gui& gui, ViewController* viewManager) 
    : View(viewManager, *gameModel, tgui::Color::Black), client(client) {
    gameModel = std::make_unique<GameModel>();
    gui.add(mainPanel);
}