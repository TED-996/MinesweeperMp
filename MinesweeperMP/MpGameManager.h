#pragma once
#include "IGameManager.h"
#include "Board.h"
#include "UiEvent.h"
#include "GameSettings.h"

namespace mMp {
	class MpGameManager : public IGameManager
	{
		Action1P<UiEvent> postUiEventAction;
		Board board;
		GameSettings gameSettings;

		int currentPlayer;
		int revealsThisTurn;
		vector<bool> playerDead;
		vector<int> scores;

	public:
		MpGameManager(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction);
		void postCommand(Command command) override;

	private:
		void handleTurnEnd(int player);
		void handleReveal(Board::BoardPoint rootPoint, int player);
		void revealPoint(Board::BoardPoint rootPoint);
		bool handleRevealAround(Board::BoardPoint rootPoint);
		int getWinner();
		void handleFlag(Board::BoardPoint point, int player);
		void KillCurrentPlayer();
	};
}
