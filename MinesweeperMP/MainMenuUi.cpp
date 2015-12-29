#include "MainMenuUi.h"

namespace mMp
{
	MainMenuUi::MainMenuUi(Action playAction, Action exitAction, Desktop& desktop)
		: UiComponent(desktop), playAction(playAction), exitAction(exitAction) {
	}

	void MainMenuUi::initWindow() {
		window->SetStyle(Style::Fullscreen);

		auto playButton = Button::Create("Play");
		playButton->GetSignal(Widget::OnLeftClick).Connect(playAction);
		auto exitButton = Button::Create("Exit");
		exitButton->GetSignal(Widget::OnLeftClick).Connect(exitAction);

		auto box = Box::Create(Box::Orientation::VERTICAL);
		box->Pack(playButton);
		box->Pack(exitButton);

		window->Add(box);
	}
}
