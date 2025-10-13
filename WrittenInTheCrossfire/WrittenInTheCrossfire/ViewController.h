#pragma once

#include "GameModel.h"
#include "GlobalWidgets.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View;

class ViewController {
	private:
		GameModel& gameModel;
		GlobalWidgets globalWidgets;
		std::shared_ptr<View> activeView;

	public:
		ViewController(GameModel& gameModel);

		enum class ViewType {
			MAIN_MENU_VIEW,
			SETTINGS_VIEW,
			ABOUT_VIEW,
			SCENE_VIEW,
			CAMP_VIEW,
			TABLE_VIEW
		};

		GlobalWidgets& getGlobalWidgets();
		std::shared_ptr<View> getActiveView();
		void setActiveView(std::shared_ptr<View> view);
		void changeView(ViewType viewType);
};