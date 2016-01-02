#pragma once
#include "UiComponent.h"
#include "MainMenuUi.h"
#include "UiEvent.h"
#include "Command.h"
#include "Board.h"

namespace mMp {
	using namespace std;
	class GameUi : public UiComponent
	{
		int boardSize;
		int mineCount;
		Button::Ptr tileButtons[Board::maxSize][Board::maxSize];

		Action closeAction;
		Action1P<Command> postCommandAction;

	public:
		GameUi(int boardSize, int mineCount, Action1P<Command> postCommandAction, Action closeAction,
			Desktop& desktop);

		void postUiEvent(UiEvent event);
	protected:
		void initWindow() override;
	private:
		Button::Ptr getNewButton(int line, int column, int size);
		void onButtonReveal(int line, int column);
		void onButtonFlag(int line, int column);
		
		void handleTileReveal(int line, int column, int neighbors);
		void handleTileFlag(int line, int column, bool flagged);

	};
}
