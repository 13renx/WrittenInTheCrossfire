#pragma once

#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ViewManager;

class View
{
	protected:
		tgui::Panel::Ptr mainPanel;
		ViewManager& viewManager;

	public:
		View(ViewManager& viewManager);
};