#include "MpHostSetupUi.h"

namespace mMp
{
	MpHostSetupUi::MpHostSetupUi(Desktop& desktop, Action backAction, Action1P<string> createServerAction,
		Action startGameAction)
		: UiComponent(desktop), backAction(backAction), createServerAction(createServerAction),
		startGameAction(startGameAction) {
	}

	extern Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment,
		Vector2f scale = Vector2f(1.0f, 1.0f));

	void MpHostSetupUi::initWindow() {
		window->SetStyle(Style::Fullscreen);
		window->GetSignal(sfg::Window::OnCloseButton).Connect(backAction);

		mainBox = Box::Create(Box::Orientation::VERTICAL, 5);

		auto nameBox = Box::Create(Box::Orientation::HORIZONTAL, 5);
		nameEntry = Entry::Create("Player 1");
		nameEntry->SetMaximumLength(10);
		auto createButton = Button::Create("Create");
		createButton->GetSignal(Widget::OnLeftClick).Connect(bind(&MpHostSetupUi::onCreateServer, this));
		
		nameBox->Pack(nameEntry, true, true);
		nameBox->Pack(createButton, false, false);

		auto nameFrame = Frame::Create("Your name:");
		nameFrame->Add(nameBox);
		nameFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.3f));
		mainBox->Pack(createAlignment(nameFrame, Vector2f(0.5f, 0.01f), Vector2f(1.0f, 0.0f)));
	}

	void MpHostSetupUi::onCreateServer() {
		string name = nameEntry->GetText();
		if (name.empty()) {
			return;
		}
		//Update UI

		nameFrame->RemoveAll();
		nameFrame->Add(Label::Create(name));

		mainBox->Pack(Label::Create("Waiting for players..."), false, false);
		playerBox = Box::Create(Box::Orientation::VERTICAL, 5);

		auto playerFrame = Frame::Create("Currently connected:");
		playerFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.5f));
		playerFrame->Add(playerBox);

		mainBox->Pack(playerFrame, true, true);

		auto startButton = Button::Create("Start game!");
		startButton->GetSignal(Widget::OnLeftClick).Connect(startGameAction);
		
		mainBox->Pack(startButton, false, false);

		createServerAction(name);
	}

	void MpHostSetupUi::addName(string name) {
		auto frame = Frame::Create();
		frame->Add(Label::Create(name));
		playerBox->Add(frame);
	}
}
