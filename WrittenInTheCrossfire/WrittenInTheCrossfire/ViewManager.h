#pragma once

#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View;

class ViewManager {
	private:
		std::shared_ptr<View> activeView;

	public:
		ViewManager(tgui::Gui& gui);

		enum class ViewType {
			MENU_VIEW,
			SETTINGS_VIEW
		};

		std::shared_ptr<View> getActiveView();
		void setActiveView(std::shared_ptr<View> view);
		void changeView(ViewType viewType, tgui::Gui& gui);
};