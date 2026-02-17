#include "GlobalWidgets.h"
#include "Macros.h"
#include "Utils.h"
#include "Widgets.h"
#include "ViewController.h"
#include <TGUI/TGUI.hpp>	
#include <TGUI/Backend/SFML-Graphics.hpp>

GlobalWidgets::GlobalWidgets(sf::RenderWindow& window, tgui::Gui& gui, ViewController* viewController) {
	// Initialize widgets
	pauseGroup = tgui::Group::create();
	pauseParentPanel = tgui::Panel::create();
	pauseChildPanel = tgui::Panel::create();
	pauseLayout = tgui::GrowVerticalLayout::create();
	pauseGamePausedLabel = Widgets::Labels::createLabel("GAME PAUSED", 60, 0, 0);
	pauseResumeLabel = Widgets::Labels::createButtonLabel("RESUME", 50, 0, 0, window);
	pauseExitLabel = Widgets::Labels::createButtonLabel("EXIT", 50, 0, 0, window);
	alertChildWindow = tgui::ChildWindow::create();
	alertLabel = Widgets::Labels::createLabel("", 13, 0, 0);
	mainPanel = tgui::Panel::create();

	pauseGroup->setVisible(false);
	pauseChildPanel->getRenderer()->setBackgroundColor(tgui::Color(28, 28, 28));
	pauseChildPanel->setSize(500, 500);
	pauseChildPanel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(pauseChildPanel)) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(pauseChildPanel)) / 2.0f);
	pauseLayout->setPosition(0, (tgui::bindHeight(pauseChildPanel) - tgui::bindHeight(pauseLayout)) / 2.0f);
	pauseLayout->getRenderer()->setSpaceBetweenWidgets(20);
	pauseGamePausedLabel->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	pauseGamePausedLabel->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	pauseResumeLabel->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	pauseExitLabel->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	alertChildWindow->setSize(400, 100);
	alertChildWindow->setCloseBehavior(tgui::ChildWindow::CloseBehavior::Hide);
	alertChildWindow->setPositionLocked(true);
	alertChildWindow->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(alertChildWindow)) / 2.0f, 0);
	alertChildWindow->setVisible(false);
	alertLabel->getRenderer()->setTextColor(tgui::Color::White);
	alertLabel->setPosition(10, 10);

	pauseResumeLabel->onClick([=, &window] {
		Utils::Log::debugInfo("pauseResumeLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		pauseGroup->setVisible(false);
	});
	pauseExitLabel->onClick([=, &window] {
		Utils::Log::debugInfo("pauseExitLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
		pauseGroup->setVisible(false);
	});
	alertChildWindow->onClose([] {
		Utils::Log::debugInfo("alertChildWindow closed");
	});

	pauseGroup->add(pauseParentPanel);
	pauseGroup->add(pauseChildPanel);
	pauseChildPanel->add(pauseLayout);
	pauseLayout->add(pauseGamePausedLabel);
	pauseLayout->add(pauseResumeLabel);
	pauseLayout->add(pauseExitLabel);
	alertChildWindow->add(alertLabel);
	gui.add(mainPanel);
	gui.add(alertChildWindow);
	gui.add(pauseGroup);
}

tgui::Group::Ptr GlobalWidgets::getPauseGroup() {
	return pauseGroup;
}

tgui::ChildWindow::Ptr GlobalWidgets::getAlertChildWindow() {
	return alertChildWindow;
}

tgui::Label::Ptr GlobalWidgets::getAlertLabel() {
	return alertLabel;
}

tgui::Panel::Ptr GlobalWidgets::getMainPanel() {
	return mainPanel;
}