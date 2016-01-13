#pragma once
#include <thread>
#include <atomic>
#include <SFML\Network.hpp>
#include "IGameManager.h"
#include "UiEvent.h"
#include "GameSettings.h"
#include "Defines.h"
#include "MpGameManager.h"

namespace mMp {
	using namespace sf;
	using namespace std;

	class HostGmAdapter : public IGameManager
	{
		MpGameManager gameManager;
		GameSettings gameSettings;
		
		vector<shared_ptr<TcpSocket>> sockets;
		SocketSelector selector;

		Action1P<UiEvent> postUiEventAction;

	public:
		HostGmAdapter(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction);

		void postCommand(Command command) override;
		bool handleEvent(Event event) override;
		void update(float seconds) override;

	private:
		void postUiEvent(UiEvent event);
		Action1P<UiEvent> getPostUiEventAction();

		void sendUiEvent(UiEvent event);
		void receiveCommand(TcpSocket& socket, int sourcePlayer);

		void disconnectPlayer(int player);

		//TODO: Adapt players!
		static Command unpackCommand(Packet packet);
		static Packet packUiEvent(UiEvent event);

		static UiEvent fakePlayer(UiEvent source, int player);
		static Command setPlayer(Command source, int player);
	};
}
