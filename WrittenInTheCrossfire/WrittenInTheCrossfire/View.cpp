#include "View.h"
#include "ViewManager.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

View::View(ViewManager* viewManager) : viewManager(viewManager) {}