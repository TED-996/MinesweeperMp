#include "GameUi.h"
#include <iostream>

namespace mMp {
	GameUi::GameUi(GameSettings gameSettings, Action1P<Command> postCommandAction, Action closeAction,
		Desktop& desktop)
		: UiComponent(desktop), gameSettings(gameSettings), scoreboard(gameSettings.names),
		selectedPoint(0, 0), closeAction(closeAction), postCommandAction(postCommandAction) {
		flaggedTiles = 0;
		playerDead.resize(gameSettings.names.size());
		currentPlayer = 0;
		reveals = 0;
		stillSelected = false;

		if (gameSettings.isMp) {
			scoreboard.setActivePlayer(0, 0, true);
		}
	}

	Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment, Vector2f scale = Vector2f(1.0f, 1.0f));

	void GameUi::initWindow() {
		window->SetStyle(Style::Fullscreen);
		window->SetRequisition(Vector2f((float)ct::WindowWidth, (float)ct::WindowHeight));

		auto mainBox = Box::Create(Box::Orientation::VERTICAL);

		auto topBox = Box::Create(Box::Orientation::HORIZONTAL);

		auto backButton = Button::Create("Back");
		backButton->GetSignal(Widget::OnLeftClick).Connect(closeAction);
		topBox->Pack(backButton, false, false);

		clockLabel = Label::Create("00:00");
		clockLabel->SetAlignment(Vector2f(1.0f, 0.5f));
		topBox->Pack(createAlignment(clockLabel, Vector2f(1.0f, 0.5f)), true, true);

		auto middleBox = Box::Create(Box::Orientation::HORIZONTAL);

		auto gameBox = Box::Create(Box::Orientation::HORIZONTAL, 5);
		auto table = Table::Create();
		int buttonSize = (int) (ct::WindowHeight * 0.7 / gameSettings.boardSize);
		for (int l = 0; l < gameSettings.boardSize; l++) {
			for (int c = 0; c < gameSettings.boardSize; c++) {
				auto tileButton = getNewButton(l, c, buttonSize);

				tileButtons[l][c] = tileButton;
				table->Attach(tileButton, Rect<Uint32>(c, l, 1, 1));
			}
		}
		gameBox->Pack(table, false, false);

		if (gameSettings.isMp) {
			auto rightPane = Box::Create(Box::Orientation::VERTICAL);
			rightPane->Pack(scoreboard.getWidget());

			auto turnFrame = Frame::Create("Turn");
			auto turnBox = Box::Create(Box::Orientation::VERTICAL, 5);

			revealCountBar = ProgressBar::Create(ProgressBar::Orientation::HORIZONTAL);
			revealCountBar->SetFraction(0);
			revealCountBar->SetRequisition(Vector2f(10, 10));
			turnBox->Pack(revealCountBar);

			auto turnEndButton = Button::Create("End turn");
			turnEndButton->GetSignal(Widget::OnLeftClick).Connect(bind(&GameUi::onTurnEnd, this));
			turnBox->Pack(turnEndButton);
			
			turnFrame->Add(turnBox);
			rightPane->Pack(turnFrame);

			gameBox->Pack(rightPane);
		}
		middleBox->Pack(createAlignment(gameBox, Vector2f(0.5f, 0.5f)));

		auto bottomBox = Box::Create(Box::Orientation::HORIZONTAL);

		messageLabel = Label::Create("Good luck!");
		messageTimeout = sf::seconds(3);
		bottomBox->Pack(messageLabel, false, true);
		bottomBox->Pack(Separator::Create(Separator::Orientation::VERTICAL), true, true);

		flagCountLabel = Label::Create(getFlagCountStr());
		auto mineCountLabel = Label::Create(string("/") + to_string(gameSettings.mineCount));
		auto mineStatBox = Box::Create(Box::Orientation::HORIZONTAL, 2);
		mineStatBox->Pack(flagCountLabel, false, false);
		mineStatBox->Pack(mineCountLabel, false, false);
		bottomBox->Pack(createAlignment(mineStatBox, Vector2f(1.0f, 0.5f), Vector2f(0.0f, 0.0f)), true, true);

		mainBox->Pack(topBox, true, true);
		mainBox->Pack(gameBox, true, true);
		mainBox->Pack(bottomBox, true, true);

		window->Add(createAlignment(mainBox, Vector2f(0.5f, 0.5f), Vector2f(0.0f, 0.0f)));

		selectTile(selectedPoint);
	}

	Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment, Vector2f scale) {
		auto result = Alignment::Create();
		result->Add(widget);
		result->SetAlignment(alignment);
		result->SetScale(scale);
		return result;
	}

	Button::Ptr GameUi::getNewButton(int line, int column, int size) {
		auto button = Button::Create();
		button->SetRequisition(Vector2f((float) size, (float) size));
		button->SetClass("Tile");

		button->GetSignal(Widget::OnLeftClick).Connect(bind(&GameUi::onButtonReveal, this, line, column));
		button->GetSignal(Widget::OnRightClick).Connect(bind(&GameUi::onButtonFlag, this, line, column));

		return button;
	}

	void GameUi::onButtonReveal(int line, int column) {
		postCommandAction(Command(Command::TileOpenCommand(line, column, currentPlayer)));
	}

	void GameUi::onButtonFlag(int line, int column) {
		postCommandAction(Command(Command::TileFlagCommand(line, column, currentPlayer)));
	}

	void GameUi::onTurnEnd() {
		postCommandAction(Command(Command::TurnEndCommand(currentPlayer)));
	}

	string timeToString(Time time);

	void GameUi::update(float seconds) {
		clockLabel->SetText(timeToString(gameClock.getElapsedTime()));

		if (messageTimeout != Time::Zero && messageTimer.getElapsedTime() >= messageTimeout) {
			messageLabel->SetText("");
			messageTimeout = Time::Zero;
		}

		if (stillSelected && selectionTimer.getElapsedTime() >= sf::seconds(4)) {
			unselectTile(selectedPoint);
		}
	}

	bool GameUi::handleEvent(Event event) {
		if (event.type != Event::KeyPressed) {
			return false;
		}
		auto keyEvent = event.key;

		if (keyEvent.code == Keyboard::Return) {
			onButtonFlag(selectedPoint.line, selectedPoint.column);
			return true;
		}
		if (keyEvent.code == Keyboard::Space) {
			onButtonReveal(selectedPoint.line, selectedPoint.column);
			return true;
		}

		Direction direction;
		if (keyEvent.code == Keyboard::Up) {
			direction = Direction::Up;
		}
		else if (keyEvent.code == Keyboard::Right) {
			direction = Direction::Right;
		}
		else if (keyEvent.code == Keyboard::Down) {
			direction = Direction::Down;
		}
		else if (keyEvent.code == Keyboard::Left) {
			direction = Direction::Left;
		}
		else {
			return false;
		}
		auto oldSelection = selectedPoint;
		selectedPoint = selectedPoint.getNeighbor(direction).clampMax(gameSettings.boardSize);
		if (oldSelection != selectedPoint) {
			unselectTile(oldSelection);
			selectTile(selectedPoint);
		}

		return true;
	}

	string timeToString(Time time) {
		ostringstream str;
		int seconds = (int)(time.asSeconds());
		str << setfill('0');
		str << setw(2) << seconds / 60 << setw(1) << ':' << setw(2) << seconds % 60;

		return str.str();
	}

	int getDigitNum(int mineCount);

	string GameUi::getFlagCountStr() {
		ostringstream str;

		int numDigits = getDigitNum(gameSettings.mineCount);
		str << "Mines: " << setfill('0') << setw(numDigits) << flaggedTiles;

		return str.str();
	}

	void GameUi::showMessage(string message, Time timeout) {
		messageLabel->SetText(message);
		messageTimeout = timeout;
		messageTimer.restart();
	}

	void GameUi::unselectTile(Board::BoardPoint boardPoint) {
		if (!stillSelected) {
			return;
		}

		auto button = tileButtons[boardPoint.line][boardPoint.column];
		auto buttonClass = button->GetClass();
		int offset = string("Selected").length();
		button->SetClass(buttonClass.substr(offset, buttonClass.length() - offset));
		stillSelected = false;
	}

	void GameUi::selectTile(Board::BoardPoint boardPoint) {
		auto button = tileButtons[boardPoint.line][boardPoint.column];
		button->SetClass("Selected" + button->GetClass());
		stillSelected = true;
		selectionTimer.restart();
	}

	int getDigitNum(int mineCount) {
		int counter = 0;
		while (mineCount != 0) {
			counter++;
			mineCount /= 10;
		}
		return counter;
	}

	void GameUi::postUiEvent(UiEvent event) {
		cout << "event got to the ui! type: " << (int) event.eventType << '\n';
		if (event.eventType == UiEvent::UiEventType::TileReveal) {
			auto tileRevealEvent = event.tileRevealEvent;
			handleTileReveal(tileRevealEvent.line, tileRevealEvent.column, tileRevealEvent.neighbors);
		}
		else if (event.eventType == UiEvent::UiEventType::TileFlag) {
			auto tileFlagEvent = event.tileFlagEvent;
			handleTileFlag(tileFlagEvent.line, tileFlagEvent.column, tileFlagEvent.flagged, tileFlagEvent.player);
		}
		else if (event.eventType == UiEvent::UiEventType::GameOver) {
			auto gameOverEvent = event.gameOverEvent;
			handleGameOver(gameOverEvent.won, gameOverEvent.player);
		}
		else if (event.eventType == UiEvent::UiEventType::PlayerDead) {
			int player = event.playerDeadEvent.player;
			handlePlayerDead(player);
		}
		else if (event.eventType == UiEvent::UiEventType::TurnStart) {
			int player = event.turnStartEvent.player;
			handleTurnStart(player);
		}
		else if (event.eventType == UiEvent::UiEventType::RevealAccepted) {
			handleRevealAccepted();
		}
	}

	void GameUi::handleTileReveal(int line, int column, int neighbors) {
		auto button = tileButtons[line][column];
		if (neighbors != 0) {
			button->SetLabel(String((char)(neighbors + '0')));
		}
		button->SetClass(button->GetClass() + "Revealed");
	}

	void GameUi::handleTileFlag(int line, int column, bool flagged, int player) {
		auto button = tileButtons[line][column];

		if (flagged) {
			button->SetClass(button->GetClass() + "Flagged");
			flaggedTiles++;
		}
		else {
			string buttonClass = button->GetClass();
			button->SetClass(buttonClass.substr(0, buttonClass.length() - string("Flagged").length()));
			flaggedTiles--;
		}

		if (gameSettings.isMp) {
			//Flag definitely added; those are checked to be correct and are never removed.
			scoreboard.incrementScore(player);
		}

		flagCountLabel->SetText(getFlagCountStr());
	}

	void GameUi::handleGameOver(bool won, int winner) {
		string message;
		if (!won) {
			message = "You lost!";
		}
		else {
			if (gameSettings.isMp) {
				message = gameSettings.names[winner] + " won!";
			}
			else {
				message = "You won!";
			}
		}
		showMessage(message, Time::Zero);
	}

	void GameUi::handlePlayerDead(int player) {
		playerDead[player] = true;
		scoreboard.setPlayerDead(player);

		showMessage(gameSettings.names[player] + " died!", sf::seconds(3));
	}

	void GameUi::handleTurnStart(int player) {
		if (gameSettings.isMp) {
			scoreboard.setActivePlayer(player, currentPlayer, playerDead[currentPlayer]);
			currentPlayer = player;

			reveals = 0;
			revealCountBar->SetFraction(0);
		}
	}

	void GameUi::handleRevealAccepted() {
		if (gameSettings.isMp) {
			if (reveals < 3) {
				reveals++;
			}
			revealCountBar->SetFraction(reveals / 3.0f);
		}
	}
}
