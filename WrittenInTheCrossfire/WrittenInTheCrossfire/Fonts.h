#pragma once

#include <TGUI/TGUI.hpp>

struct Fonts {
    static tgui::Font Title;
    static tgui::Font Writing;
    static tgui::Font Default;

    static void load();
};