#include "GlobalWidgets.h"

GlobalWidgets::GlobalWidgets(tgui::Gui& gui) {
	alertChildWindow = tgui::ChildWindow::create();
	alertLabel = Widgets::Labels::createLabel("", 13, 0, 0);
	mainPanel = tgui::Panel::create();

	alertChildWindow->setSize(400, 100);
	alertChildWindow->setCloseBehavior(tgui::ChildWindow::CloseBehavior::Hide);
	alertChildWindow->setPositionLocked(true);
	alertChildWindow->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(alertChildWindow)) / 2.0f, 0);
	alertChildWindow->setVisible(false);
	alertLabel->setPosition(10, 10);

	alertChildWindow->add(alertLabel);
	gui.add(mainPanel);
	gui.add(alertChildWindow);
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