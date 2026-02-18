#pragma once

#include "GameModel.h"
#include "StoryModel.h"
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
			MAIN_SCENE_VIEW,
			READ_LETTER_VIEW,
			CAMP_VIEW,
			WRITE_LETTER_VIEW,
			MAP_VIEW,
			LOCATION_SCENE_VIEW_BUNK,
			LOCATION_SCENE_VIEW_STORAGE,
			LOCATION_SCENE_VIEW_MEAL
		};

	private:
		GameModel& gameModel;
		std::shared_ptr<GlobalWidgets> globalWidgets;
		StoryModel storyModel;
		ViewType activeViewType;
		std::shared_ptr<View> activeView;

	public:
		ViewController(GameModel& gameModel);

		std::shared_ptr<GlobalWidgets> getGlobalWidgets();
		ViewType& getActiveViewType();
		void changeView(ViewType viewType);
};