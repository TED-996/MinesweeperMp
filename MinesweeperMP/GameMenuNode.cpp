#include "GameMenuNode.h"
#include "GameUi.h"
#include "SpGameManager.h"
#include "MpGameManager.h"
#include "ClientGmAdapter.h"
#include "HostGmAdapter.h"

namespace mMp {
	GameMenuNode::GameMenuNode(GameSettings gameSettings, Action closeAction, Desktop& desktop)
		: MenuNode(desktop,
			make_shared<GameUi>(gameSettings, getPostCommandAction(), closeAction, desktop)){
		if (gameSettings.isMp) {
			if (gameSettings.isLocal) {
				gameManager = make_shared<MpGameManager>(gameSettings, getPostUiEventAction());
			}
			else {
				if (gameSettings.isRemote) {
					gameManager = make_shared<ClientGmAdapter>(gameSettings, getPostUiEventAction());
				}
				else {
					gameManager = make_shared<HostGmAdapter>(gameSettings, getPostUiEventAction());
				}
			}
		}
		else {
			gameManager = make_shared<SpGameManager>(gameSettings, getPostUiEventAction());
		}
	}

	bool GameMenuNode::handleEvent(Event event) {
		if (MenuNode::handleEvent(event)) {
			return true;
		}
		if (gameManager->handleEvent(event)) {
			return true;
		}
		return false;
	}

	void GameMenuNode::update(float seconds) {
		MenuNode::update(seconds);
		gameManager->update(seconds);
	}

	void GameMenuNode::postUiCommand(Command command) {
		gameManager->postCommand(command);
	}

	void GameMenuNode::postUiEvent(UiEvent uiEvent) {
		(dynamic_pointer_cast<GameUi>(uiComponent))->postUiEvent(uiEvent);
	}

	Action1P<Command> GameMenuNode::getPostCommandAction() {
		return bind(&GameMenuNode::postUiCommand, this, placeholders::_1);
	}

	Action1P<UiEvent> GameMenuNode::getPostUiEventAction() {
		return bind(&GameMenuNode::postUiEvent, this, placeholders::_1);
	}
}
