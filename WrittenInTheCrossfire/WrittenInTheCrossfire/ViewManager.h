#pragma once

#include "Client.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View;

class ViewManager {
	private:
		Client client;
		tgui::Gui& gui;
		std::shared_ptr<View> activeView;

	public:
		ViewManager(tgui::Gui& gui);

		enum class ViewType {
			MENU_VIEW,
			SETTINGS_VIEW,
			CAMP_VIEW,
			TABLE_VIEW
		};

		std::shared_ptr<View> getActiveView();
		void setActiveView(std::shared_ptr<View> view);
		void changeView(ViewType viewType);
};