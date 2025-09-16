#include "Screen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

Screen::Screen(tgui::Gui& g) : panel(tgui::Panel::create()), gui(g) {}