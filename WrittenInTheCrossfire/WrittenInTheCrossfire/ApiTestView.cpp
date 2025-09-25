#include "ApiTestView.h"
#include "Widgets.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

ApiTestView::ApiTestView(Client& client, tgui::Gui& gui, ViewManager* viewManager) : View(gui, viewManager, "") {
    
}