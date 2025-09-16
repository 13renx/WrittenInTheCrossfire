#include "MenuManager.h"

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuManager::MenuManager(tgui::Gui& g) : Manager(MenuScreen(g), MenuScript(g)) {}