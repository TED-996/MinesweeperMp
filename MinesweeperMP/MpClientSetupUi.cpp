#include "MpClientSetupUi.h"
#include "Defines.h"

namespace mMp {
	MpClientSetupUi::MpClientSetupUi(Desktop& desktop, Action backAction, Action1P<string> setNameAction,
		Action1P<int> selectServerAction)
		: UiComponent(desktop), backAction(backAction), setNameAction(setNameAction),
		selectServerAction(selectServerAction) {
		serverCount = 0;
	}

	extern Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment,
		Vector2f scale = Vector2f(1.0f, 1.0f));

	void MpClientSetupUi::initWindow() {
		window->SetStyle(Style::Fullscreen | Style::Close);
		window->GetSignal(sfg::Window::OnCloseButton).Connect(backAction);
		mainBox = Box::Create(Box::Orientation::VERTICAL, 5);

		nameEntry = Entry::Create("Player 1");
		nameEntry->SetMaximumLength(10);

		auto nameFrame = Frame::Create("Your name:");
		nameFrame->Add(nameEntry);
		nameFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.3f));
		mainBox->Pack(createAlignment(nameFrame, Vector2f(0.5f, 0.0f), Vector2f(1.0f, 0.0f)));

		serverBox = Box::Create(Box::Orientation::VERTICAL, 5);
		auto serverFrame = Frame::Create("Avaliable servers:");
		serverFrame->Add(serverBox);
		serverFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.5f));

		mainBox->Pack(serverFrame, true, true);
	}

	void MpClientSetupUi::addServer(string name) {
		auto serverButton = Button::Create(name);
		serverButton->GetSignal(Widget::OnLeftClick).Connect(
			bind(&MpClientSetupUi::selectServer, this, serverCount));
		serverCount++;

		serverBox->Pack(serverButton);
	}
 
	void MpClientSetupUi::selectServer(int index) {
		setNameAction(nameEntry->GetText());
		selectServerAction(index);
	}
}
