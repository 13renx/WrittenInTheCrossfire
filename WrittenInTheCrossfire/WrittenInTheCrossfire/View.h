#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View
{
	protected:
		tgui::Panel::Ptr mainPanel;
		std::shared_ptr<View> activeView;

	public:
		View(std::shared_ptr<View> v);

		std::shared_ptr<View> getActiveView();
		void setActiveView(std::shared_ptr<View> activeView);
};