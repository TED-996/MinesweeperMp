#include "ClientGmAdapter.h"

namespace mMp {
	ClientGmAdapter::ClientGmAdapter(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction)
		: socket(gameSettings.sockets[0]), postUiEventAction(postUiEventAction) {
		socket->setBlocking(false);
	}

	void ClientGmAdapter::postCommand(Command command) {
		if (socket == nullptr) {
			return;
		}

		Packet packet = packCommand(command);
		if (socket->send(packet) != Socket::Done) {
			socket->disconnect();
			socket = nullptr;
		}
	}

	bool ClientGmAdapter::handleEvent(Event event) {
		if (event.type == Event::Closed) {
			socket->disconnect();
		}
		return false;
	}

	void ClientGmAdapter::update(float seconds) {
		Packet packet;
		if (socket->receive(packet) == Socket::Done) {
			postUiEventAction(unpackEvent(packet));
		}
	}
}
