#pragma once

#include "Screen.h"
#include "Script.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Manager
{
	protected:
		Screen screen;
		Script script;

	public:
		Manager(Screen s, Script sc);
};