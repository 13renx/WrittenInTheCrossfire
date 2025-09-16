#include "Manager.h"
#include "Screen.h"
#include "Script.h"

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

Manager::Manager(Screen s, Script sc) : screen(s), script(sc) {}