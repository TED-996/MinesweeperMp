#include "MainMenu.h"
#include "Constants.h"

namespace mMp
{
	MainMenu::MainMenu(function<void()> newCloseFunction) {
		closeFunction = newCloseFunction;
	}

	void MainMenu::onPlayClick() {
		printf("don't do that!");
	}

	void MainMenu::onExitClick() {
		closeFunction();
	}

	void MainMenu::initWindow() {
		window = sfg::Window::Create(Style::Fullscreen);

		auto playButton = Button::Create("Play");
		playButton->GetSignal(Widget::OnLeftClick).Connect(bind(&MainMenu::onPlayClick, this));
		auto exitButton = Button::Create("Exit");
		exitButton->GetSignal(Widget::OnLeftClick).Connect(bind(&MainMenu::onExitClick, this));

		auto box = Box::Create(Box::Orientation::VERTICAL, 5);
		box->SetRequisition(Vector2f(ct::WindowWidth - 25, ct::WindowHeight - 25));

		box->Pack(playButton, true);
		box->Pack(exitButton, true, true);

		window->Add(box);
	}
}
