#pragma once

#include "Manager.h"
#include "MenuScreen.h"
#include "MenuScript.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuManager : public Manager
{
	public:
		MenuManager(tgui::Gui& g);
};