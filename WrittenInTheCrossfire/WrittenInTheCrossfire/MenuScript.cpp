#include "MenuScript.h"

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuScript::MenuScript(tgui::Gui& g) : Script(g) {
	exitLabel = g.get<tgui::Label>("ExitLabel");
	exitPanel = g.get<tgui::Panel>("ExitPanel");
	exitGroup = g.get<tgui::Group>("ExitGroup");

	exitLabel->onClick([](tgui::Group::Ptr group) { group->setVisible(true); }, exitGroup);
	exitPanel->onClick([](tgui::Group::Ptr group) { group->setVisible(false); }, exitGroup);
}