#pragma once

#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ApiTestView : public View {
    public:
        ApiTestView(Client& client, tgui::Gui& gui, ViewManager* viewManager);
};