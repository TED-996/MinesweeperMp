#pragma once
#include <memory>
#include <SFML/Network.hpp>
#include "MenuNode.h"
#include "GameSettings.h"
#include "MpHostSetupUi.h"

namespace mMp {
	class MpHostSetupNode : public MenuNode
	{
		Action closeAction;

		GameSettings gameSettings;
		bool serverWaiting;

		Clock broadcastTimer;
		TcpListener listener;

		shared_ptr<MpHostSetupUi> customUiComponent;
	public:
		MpHostSetupNode(GameSettings gameSettings, Action closeAction, Desktop& sfgDesktop);

		bool handleEvent(Event event) override;
		void update(float seconds) override;
	private:
		void broadcastHost();

		Action1P<string> getCreateServerAction();
		Action getStartGameAction();

		void createServer(string playerName);
		void startGame();
		void sendGameSettings();

		void closeSockets();
	};
}
