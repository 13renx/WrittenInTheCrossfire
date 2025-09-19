#pragma once

#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View
{
	protected:
		tgui::Panel::Ptr mainPanel;
		ViewManager*& viewManager;

	public:
		View(ViewManager*& viewManager);
};