#include "View.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

View::View(tgui::Gui& g, std::shared_ptr<View> v) : panel(tgui::Panel::create()), gui(g), activeView(v) {}