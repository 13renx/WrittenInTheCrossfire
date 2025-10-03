#pragma once

#include "GameModel.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View;

class ViewController {
	private:
		GameModel& gameModel;
		std::shared_ptr<View> activeView;

	public:
		ViewController(GameModel& gameModel);

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