#pragma once
#include "memory"
#include "MenuNode.h"
#include "GameSettings.h"
#include "MpHostSetupUi.h"

namespace mMp {
	class MpHostSetupNode : public MenuNode
	{
		Action closeAction;

		GameSettings gameSettings;

		shared_ptr<MpHostSetupUi> customUiComponent;
	public:
		explicit MpHostSetupNode(Desktop& sfgDesktop, Action closeAction, GameSettings gameSettings);

	private:
		Action1P<string> getCreateServerAction();
		Action getStartGameAction();

		void createServer(string playerName);
		void startGame();
	};
}
