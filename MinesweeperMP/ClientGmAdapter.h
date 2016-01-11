#pragma once
#include <SFML/Network.hpp>
#include "IGameManager.h"
#include "UiEvent.h"
#include "GameSettings.h"
#include "Defines.h"

namespace mMp {
	using namespace sf;
	using namespace std;
	class ClientGmAdapter : IGameManager
	{
		shared_ptr<TcpSocket> socket;

		Action1P<UiEvent> postUiEventAction;
	public:
		ClientGmAdapter(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction);

		void postCommand(Command command) override;
		bool handleEvent(Event event) override;
		void update(float seconds) override;
	private:
		Packet packCommand(Command command);
		UiEvent unpackEvent(Packet packet);
	};
}
