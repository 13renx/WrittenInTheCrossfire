#pragma once

#include "GameModel.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class GlobalWidgets;
class View;

class ViewController {
	public:
		enum class ViewType {
			MAIN_MENU_VIEW,
			SETTINGS_VIEW,
			ABOUT_VIEW,
			SCENE_VIEW,
			CAMP_VIEW,
			TABLE_VIEW
		};

	private:
		GameModel& gameModel;
		std::shared_ptr<GlobalWidgets> globalWidgets;
		std::shared_ptr<View> activeView;
		ViewType activeViewType;

	public:
		ViewController(GameModel& gameModel);

		std::shared_ptr<GlobalWidgets> getGlobalWidgets();
		ViewType& getActiveViewType();
		void changeView(ViewType viewType);
};