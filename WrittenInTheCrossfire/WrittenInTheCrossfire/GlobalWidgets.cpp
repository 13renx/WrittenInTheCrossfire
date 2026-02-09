#include "GlobalWidgets.h"
#include "Macros.h"
#include "Utils.h"
#include "Widgets.h"
#include "ViewController.h"
#include <TGUI/TGUI.hpp>	
#include <TGUI/Backend/SFML-Graphics.hpp>

GlobalWidgets::GlobalWidgets(sf::RenderWindow& window, tgui::Gui& gui, ViewController* viewController) {
	// Initialize widgets
	menuParentPanel = tgui::Panel::create();
	menuChildPanel = tgui::Panel::create();
	menuLayout = tgui::GrowVerticalLayout::create();
	menuResumeLabel = Widgets::Labels::createButtonLabel("RESUME", 50, 0, 0, window);
	menuExitLabel = Widgets::Labels::createButtonLabel("EXIT", 50, 0, 0, window);
	alertChildWindow = tgui::ChildWindow::create();
	alertLabel = Widgets::Labels::createLabel("", 13, 0, 0);
	mainPanel = tgui::Panel::create();

	menuParentPanel->setVisible(false);
	menuChildPanel->setSize(450, 450);
	menuChildPanel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(menuChildPanel)) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(menuChildPanel)) / 2.0f);
	menuLayout->setPosition(0, (tgui::bindHeight(menuChildPanel) - tgui::bindHeight(menuLayout)) / 2.0f);
	menuLayout->getRenderer()->setSpaceBetweenWidgets(20);
	menuResumeLabel->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	menuExitLabel->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	alertChildWindow->setSize(400, 100);
	alertChildWindow->setCloseBehavior(tgui::ChildWindow::CloseBehavior::Hide);
	alertChildWindow->setPositionLocked(true);
	alertChildWindow->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(alertChildWindow)) / 2.0f, 0);
	alertChildWindow->setVisible(false);
	alertLabel->getRenderer()->setTextColor(tgui::Color::White);
	alertLabel->setPosition(10, 10);

	menuResumeLabel->onClick([=, &window] {
		Utils::Log::info("menuResumeLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		menuParentPanel->setVisible(false);
	});
	menuExitLabel->onClick([=, &window] {
		Utils::Log::info("menuExitLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
		menuParentPanel->setVisible(false);
	});
	alertChildWindow->onClose([] {
		Utils::Log::info("alertChildWindow closed");
	});

	menuParentPanel->add(menuChildPanel);
	menuChildPanel->add(menuLayout);
	menuLayout->add(menuResumeLabel);
	menuLayout->add(menuExitLabel);
	alertChildWindow->add(alertLabel);
	gui.add(mainPanel);
	gui.add(alertChildWindow);
	gui.add(menuParentPanel);
}

tgui::Panel::Ptr GlobalWidgets::getMenuParentPanel() {
	return menuParentPanel;
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