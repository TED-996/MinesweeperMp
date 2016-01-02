#include "GameUi.h"
#include <iostream>

namespace mMp {
	GameUi::GameUi(int boardSize, int mineCount, Action1P<Command> postCommandAction, Action closeAction,
		Desktop& desktop)
		: UiComponent(desktop), boardSize(boardSize), mineCount(mineCount), closeAction(closeAction),
		postCommandAction(postCommandAction) {
	}

	void GameUi::initWindow() {
		window->SetStyle(Style::Fullscreen);

		auto introLabel = Label::Create("Find the mines!");
		auto backButton = Button::Create("Back");
		backButton->GetSignal(Widget::OnLeftClick).Connect(closeAction);
		auto introBox = Box::Create(Box::Orientation::VERTICAL, 5);
		introBox->Pack(introLabel);
		introBox->Pack(backButton);

		auto table = Table::Create();
		int buttonSize = (int) (ct::WindowHeight * 0.8 / boardSize);
		for (int l = 0; l < boardSize; l++) {
			for (int c = 0; c < boardSize; c++) {
				auto tileButton = getNewButton(l, c, buttonSize);

				tileButtons[l][c] = tileButton;
				table->Attach(tileButton, Rect<Uint32>(l, c, 1, 1));
			}
		}
		
		auto fixedContainer = Fixed::Create();
		fixedContainer->Put(introBox, Vector2f(10, 10));
		fixedContainer->Put(table, Vector2f((ct::WindowWidth - boardSize * buttonSize) / 2,
			(ct::WindowHeight - boardSize * buttonSize) / 2));

		window->Add(fixedContainer);
	}

	Button::Ptr GameUi::getNewButton(int line, int column, int size) {
		auto button = Button::Create();
		button->SetRequisition(Vector2f(size, size));
		button->SetClass("Tile");

		button->GetSignal(Widget::OnLeftClick).Connect(bind(&GameUi::onButtonReveal, this, line, column));
		button->GetSignal(Widget::OnRightClick).Connect(bind(&GameUi::onButtonFlag, this, line, column));

		return button;
	}

	void GameUi::onButtonReveal(int line, int column) {
		postCommandAction(Command(Command::TileOpenCommand(line, column)));
	}

	void GameUi::onButtonFlag(int line, int column) {
		postCommandAction(Command(Command::TileFlagCommand(line, column)));
	}

	void GameUi::postUiEvent(UiEvent event) {
		cout << "event got to the ui! type: " << (int) event.eventType << '\n';
		if (event.eventType == UiEvent::UiEventType::TileReveal) {
			handleTileReveal(event.tileRevealEvent.line, event.tileRevealEvent.column,
				event.tileRevealEvent.neighbors);
		}
		else if (event.eventType == UiEvent::UiEventType::TileFlag) {
			handleTileFlag(event.tileFlagEvent.line, event.tileFlagEvent.column, event.tileFlagEvent.flagged);
		}
		else if (event.eventType == UiEvent::UiEventType::GameOver) {
			closeAction();
		}
	}


	void GameUi::handleTileReveal(int line, int column, int neighbors) {
		auto button = tileButtons[line][column];
		if (neighbors != 0) {
			button->SetLabel(String((char)(neighbors + '0')));
		}
		button->SetClass("Revealed");
	}

	void GameUi::handleTileFlag(int line, int column, bool flagged) {
		auto button = tileButtons[line][column];
		button->SetClass((flagged ? "Flagged" : "Tile"));
	}
}
