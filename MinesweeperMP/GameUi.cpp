#include "GameUi.h"

namespace mMp {
	GameUi::GameUi(Action closeAction, Desktop& desktop)
		: UiComponent(desktop), closeAction(closeAction) {
	}

	void GameUi::initWindow() {
		window->SetStyle(Style::Fullscreen);

		auto label = Label::Create("If you see this, it's working.");
		auto button = Button::Create("Back");
		button->GetSignal(Widget::OnLeftClick).Connect(closeAction);

		auto box = Box::Create(Box::Orientation::VERTICAL);
		box->Pack(label);
		box->Pack(button);

		window->Add(box);
	}
}
