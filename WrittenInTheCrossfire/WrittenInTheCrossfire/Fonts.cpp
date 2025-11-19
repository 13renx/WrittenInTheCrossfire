#include "Fonts.h"

tgui::Font Fonts::Title;
tgui::Font Fonts::Writing;
tgui::Font Fonts::Default;

void Fonts::load()
{
    Fonts::Title = tgui::Font{ "Assets/Fonts/HomemadeApple.ttf" };
    Fonts::Writing = tgui::Font{ "Assets/Fonts/Caveat.ttf" };
    Fonts::Default = tgui::Font{ "Assets/Fonts/Inconsolata.ttf" };
}
