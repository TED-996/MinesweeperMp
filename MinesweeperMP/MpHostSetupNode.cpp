#include "MpHostSetupNode.h"
#include "MpHostSetupUi.h"
#include "GameMenuNode.h"

namespace mMp
{
	MpHostSetupNode::MpHostSetupNode(Desktop& sfgDesktop, Action closeAction, GameSettings gameSettings)
		: MenuNode(sfgDesktop,
			make_shared<MpHostSetupUi>(sfgDesktop, getCreateServerAction(), getStartGameAction())), 
			closeAction(closeAction), gameSettings(gameSettings) {
		customUiComponent = dynamic_pointer_cast<MpHostSetupUi>(uiComponent);
	}

	Action1P<string> MpHostSetupNode::getCreateServerAction() {
		return bind(&MpHostSetupNode::createServer, this, placeholders::_1);
	}

	Action MpHostSetupNode::getStartGameAction() {
		return bind(&MpHostSetupNode::startGame, this);
	}

	void MpHostSetupNode::createServer(string playerName) {
		customUiComponent->addName("No one yet, but it's working.");
		gameSettings.names.push_back(playerName);
		gameSettings.sockets.push_back(nullptr);
	}

	void MpHostSetupNode::startGame() {
		setChild(make_shared<GameMenuNode>(gameSettings, closeAction, sfgDesktop));
	}
}
