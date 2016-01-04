#include "GameMenuNode.h"
#include "GameUi.h"
#include "SpGameManager.h"
#include "LocalMpGameManager.h"

namespace mMp {
	GameMenuNode::GameMenuNode(GameSettings gameSettings, Action closeAction, Desktop& desktop)
		: MenuNode(desktop,
			make_shared<GameUi>(gameSettings, getPostCommandFunction(), closeAction, desktop)){
		if (gameSettings.isMp) {
			gameManager = make_shared<LocalMpGameManager>(gameSettings, getPostUiEventFunction());
		}
		else {
			gameManager = make_shared<SpGameManager>(gameSettings, getPostUiEventFunction());
		}
	}

	void GameMenuNode::postUiCommand(Command command) {
		gameManager->postCommand(command);
	}

	void GameMenuNode::postUiEvent(UiEvent uiEvent) {
		(dynamic_pointer_cast<GameUi>(uiComponent))->postUiEvent(uiEvent);
	}

	Action1P<Command> GameMenuNode::getPostCommandFunction() {
		return bind(&GameMenuNode::postUiCommand, this, placeholders::_1);
	}

	Action1P<UiEvent> GameMenuNode::getPostUiEventFunction() {
		return bind(&GameMenuNode::postUiEvent, this, placeholders::_1);
	}
}
