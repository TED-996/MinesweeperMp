#include "GameMenuNode.h"
#include "GameUi.h"


namespace mMp {
	GameMenuNode::GameMenuNode(int boardSize, int mineCount, Action closeAction, Desktop& desktop)
		: MenuNode(desktop,
			make_shared<GameUi>(boardSize, mineCount, getPostCommandFunction(), closeAction, desktop)),
		gameManager(boardSize, mineCount, getPostUiEventFunction()) {
	}

	void GameMenuNode::postUiCommand(Command command) {
		gameManager.postCommand(command);
	}

	void GameMenuNode::postUiEvent(UiEvent uiEvent) {
		(dynamic_pointer_cast<GameUi>(uiComponent))->postUiEvent(uiEvent);
	}

	function<void(Command)> GameMenuNode::getPostCommandFunction() {
		return bind(&GameMenuNode::postUiCommand, this, placeholders::_1);
	}

	function<void(UiEvent)> GameMenuNode::getPostUiEventFunction() {
		return bind(&GameMenuNode::postUiEvent, this, placeholders::_1);
	}
}
