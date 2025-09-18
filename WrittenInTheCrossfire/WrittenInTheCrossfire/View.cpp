#include "View.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

View::View(std::shared_ptr<View> v) : activeView(v) {}

std::shared_ptr<View> View::getActiveView() {
	return activeView;
}

void View::setActiveView(std::shared_ptr<View> activeView) {
	this->activeView = activeView;
}