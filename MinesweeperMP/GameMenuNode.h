#pragma once
#include "MenuNode.h"
#include "GameManager.h"

namespace mMp {
	class GameMenuNode : public MenuNode
	{
		GameManager gameManager;
	public:
		GameMenuNode(Desktop& desktop, Action closeAction);

	private:
		void postUiCommand(Command command);
		void postUiEvent(UiEvent uiEvent);
		Action1P<Command> getPostCommandFunction();
		Action1P<UiEvent> getPostUiEventFunction();
	};
}
