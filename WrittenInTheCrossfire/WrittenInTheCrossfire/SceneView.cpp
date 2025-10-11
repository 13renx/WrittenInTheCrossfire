#include "SceneView.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SceneView::SceneView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("")) {
	dialoguePanel = tgui::Panel::create();
	dialogueText = Widgets::Labels::createLabel("", 25, 0, 0);
}