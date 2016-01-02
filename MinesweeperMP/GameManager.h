#pragma once
#include "Command.h"
#include "Defines.h"
#include "UiEvent.h"
#include "Component.h"
#include "Board.h"

namespace mMp {
	class GameManager : public Component
	{
		Action1P<UiEvent> postUiEventAction;
		Board board;
	public:
		explicit GameManager(int boardSize, int mineCount, Action1P<UiEvent> postUiEventAction);

		void postCommand(Command command);

	private:
		void handleReveal(Board::BoardPoint rootPoint);
	};
}
