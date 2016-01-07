#pragma once
#include "UiComponent.h"
#include "MainMenuUi.h"
#include "UiEvent.h"
#include "Command.h"
#include "Board.h"
#include "GameSettings.h"
#include "Scoreboard.h"

namespace mMp {
	using namespace std;
	class GameUi : public UiComponent
	{
		GameSettings gameSettings;
		Button::Ptr tileButtons[Board::maxSize][Board::maxSize];
		Scoreboard scoreboard;
		vector<bool> playerDead;
		int currentPlayer;
		int reveals;

		Clock gameClock;
		Label::Ptr clockLabel;

		int flaggedTiles;
		Label::Ptr flagCountLabel;
		ProgressBar::Ptr revealCountBar;

		Board::BoardPoint selectedPoint;
		bool stillSelected;
		Clock selectionTimer;

		Label::Ptr messageLabel;
		Clock messageTimer;
		Time messageTimeout;

		Action closeAction;
		Action1P<Command> postCommandAction;

	public:
		GameUi(GameSettings gameSettings, Action1P<Command> postCommandAction, Action closeAction,
			Desktop& desktop);

		void postUiEvent(UiEvent event);

		void update(float seconds) override;
		bool handleEvent(Event event) override;
	protected:
		void initWindow() override;
	private:
		Button::Ptr getNewButton(int line, int column, int size);
		void onButtonReveal(int line, int column);
		void onButtonFlag(int line, int column);
		void onTurnEnd();

		string getFlagCountStr();
		void showMessage(string message, Time timeout);

		void unselectTile(Board::BoardPoint boardPoint);
		void selectTile(Board::BoardPoint boardPoint);
		
		void handleTileReveal(int line, int column, int neighbors);
		void handleTileFlag(int line, int column, bool flagged, int player);
		void handleGameOver(bool won, int winner);
		void handlePlayerDead(int player);
		void handleTurnStart(int player);
		void handleRevealAccepted();

	};
}
