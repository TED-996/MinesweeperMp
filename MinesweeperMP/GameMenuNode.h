#pragma once
#include "MenuNode.h"
#include "SpGameManager.h"

namespace mMp {
	class GameMenuNode : public MenuNode
	{
		shared_ptr<IGameManager> gameManager;
	public:
		GameMenuNode(GameSettings gameSettings, Action closeAction, Desktop& desktop);


		bool handleEvent(Event event) override;
		void update(float seconds) override;
	private:
		void postUiCommand(Command command);
		void postUiEvent(UiEvent uiEvent);
		Action1P<Command> getPostCommandFunction();
		Action1P<UiEvent> getPostUiEventFunction();
	};
}
