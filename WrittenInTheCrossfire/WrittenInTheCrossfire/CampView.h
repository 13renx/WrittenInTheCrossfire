#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class CampView : public View
{
	private:
		Client& client;
		GameModel gameModel;



	public:
		CampView(Client& client, tgui::Gui& gui, ViewManager* viewManager);
};