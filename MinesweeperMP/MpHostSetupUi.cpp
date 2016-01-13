#include "MpHostSetupUi.h"

namespace mMp
{
	MpHostSetupUi::MpHostSetupUi(Desktop& desktop, Action backAction, Action1P<string> createServerAction,
		Action startGameAction)
		: UiComponent(desktop), backAction(backAction), createServerAction(createServerAction),
		startGameAction(startGameAction) {
		doCreateServer = false;
	}

	extern Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment,
		Vector2f scale = Vector2f(1.0f, 1.0f));

	void MpHostSetupUi::initWindow() {
		window->SetStyle(Style::Fullscreen);
		window->SetRequisition(Vector2f((float)ct::WindowWidth, (float)ct::WindowHeight));

		mainBox = Box::Create(Box::Orientation::VERTICAL, 5);
		auto closeButton = Button::Create("Close");
		closeButton->GetSignal(Widget::OnLeftClick).Connect(backAction);
		mainBox->Pack(createAlignment(closeButton, Vector2f(0.0f, 0.0f), Vector2f(1.0f, 0.0f)));

		auto nameBox = Box::Create(Box::Orientation::HORIZONTAL, 5);
		nameEntry = Entry::Create("Player 1");
		nameEntry->SetMaximumLength(10);
		nameEntry->SetRequisition(Vector2f(ct::WindowWidth * 0.1f, 0.0f));
		auto createButton = Button::Create("Create");
		createButton->GetSignal(Widget::OnLeftClick).Connect(bind(&MpHostSetupUi::triggerCreateServer, this));
		
		nameBox->Pack(nameEntry, true, true);
		nameBox->Pack(createButton, true, true);

		nameFrame = Frame::Create("Your name:");
		nameFrame->Add(nameBox);
		nameFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.1f));
		mainBox->Pack(createAlignment(nameFrame, Vector2f(0.5f, 0.01f), Vector2f(1.0f, 0.0f)));

		window->Add(createAlignment(mainBox, Vector2f(0.5f, 0.5f), Vector2f(0.9f, 0.9f)));
	}

	void MpHostSetupUi::update(float seconds) {
		if (doCreateServer) {
			createServer();
			doCreateServer = false;
		}
	}

	void MpHostSetupUi::triggerCreateServer() {
		doCreateServer = true;
	}

	void MpHostSetupUi::createServer() {
		string name = nameEntry->GetText();
		if (name.empty()) {
			return;
		}
		nameEntry = nullptr;

		nameFrame->RemoveAll();
		auto nameLabel = Label::Create(name);
		nameLabel->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.05f));
		nameLabel->SetAlignment(Vector2f(0.5f, 0.5f));
		nameFrame->Add(createAlignment(nameLabel, Vector2f(0.5f, 0.5f), Vector2f(0.0f, 0.0f)));


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
		playerBox->Pack(frame);
	}
}
