#pragma once
#include "Command.h"
#include "Defines.h"
#include "UiEvent.h"
#include "Board.h"
#include "GameSettings.h"
#include "IGameManager.h"

namespace mMp {
	class SpGameManager : public IGameManager
	{
		Action1P<UiEvent> postUiEventAction;
		Board board;

		bool gameOver;

	public:
		SpGameManager(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction);

		void postCommand(Command command) override;

	private:
		void handleReveal(Board::BoardPoint rootPoint);
		void handleRevealAround(Board::BoardPoint rootPoint);
	};
}
