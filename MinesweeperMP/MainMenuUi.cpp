#include "MainMenuUi.h"

namespace mMp
{
	MainMenuUi::MainMenuUi(Action playSpAction, Action playLocalMpAction, Action hostMpAction, Action joinMpAction,
		Action exitAction, Desktop& desktop)
		: UiComponent(desktop), playSpAction(playSpAction), playLocalMpAction(playLocalMpAction),
		hostMpAction(hostMpAction), joinMpAction(joinMpAction), exitAction(exitAction) {
	}

	extern Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment,
		Vector2f scale = Vector2f(1.0f, 1.0f));

	void MainMenuUi::initWindow() {
		window->SetStyle(Style::Fullscreen);
		window->SetRequisition(Vector2f((float) ct::WindowWidth, (float) ct::WindowHeight));

		auto mMpLabel = Label::Create("Minesweeper: Multiplayer Edition");
		mMpLabel->SetAlignment(Vector2f(0.5f, 0.5f));
		mMpLabel->SetClass("MMpLabel");

		auto playSpButton = Button::Create("Play Singleplayer");
		playSpButton->GetSignal(Widget::OnLeftClick).Connect(playSpAction);
		auto playLocalMpButton = Button::Create("Play Local Multiplayer");
		playLocalMpButton->GetSignal(Widget::OnLeftClick).Connect(playLocalMpAction);
		auto hostMpButton = Button::Create("Create a multiplayer server");
		hostMpButton->GetSignal(Widget::OnLeftClick).Connect(hostMpAction);
		auto joinMpButton = Button::Create("Join a multiplayer server");
		joinMpButton->GetSignal(Widget::OnLeftClick).Connect(joinMpAction);

		auto exitButton = Button::Create("Exit");
		exitButton->GetSignal(Widget::OnLeftClick).Connect(exitAction);

		auto mainBox = Box::Create(Box::Orientation::VERTICAL, 2);
		auto playBox = Box::Create(Box::Orientation::VERTICAL, 2);
		playBox->Pack(playSpButton);
		playBox->Pack(playLocalMpButton);
		playBox->Pack(hostMpButton);
		playBox->Pack(joinMpButton);
		auto playFrame = Frame::Create("Play");
		playFrame->Add(playBox);
		playFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.4f));

		mainBox->Pack(mMpLabel);
		mainBox->Pack(playFrame);
		mainBox->Pack(exitButton);

		window->Add(createAlignment(mainBox, Vector2f(0.5f, 0.5f), Vector2f(0.7f, 0.7f)));
	}
}
