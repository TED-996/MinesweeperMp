#include "HostGmAdapter.h"
#include <iostream>

namespace mMp
{
	HostGmAdapter::HostGmAdapter(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction)
		: gameManager(gameSettings, getPostUiEventAction()), gameSettings(gameSettings),
		sockets(gameSettings.sockets), postUiEventAction(postUiEventAction) {
		for (auto socket : sockets) {
			if (socket != nullptr) {
				selector.add(*socket);
				socket->setBlocking(false);
			}
		}
	}

	void HostGmAdapter::postCommand(Command command) {
		gameManager.postCommand(command);
	}

	bool HostGmAdapter::handleEvent(Event event) {
		if (event.type == Event::Closed) {
			for (auto socket : sockets) {
				if (socket != nullptr) {
					socket->disconnect();
				}
			}
		}
		return false;
	}

	void HostGmAdapter::update(float seconds) {
		for (int i = 0; i < (int) sockets.size(); i++) {
			if (sockets[i] != nullptr && selector.isReady(*sockets[i])) {
				receiveCommand(*sockets[i], i);
			}
		}
	}

	void HostGmAdapter::postUiEvent(UiEvent event) {
		postUiEventAction(event);
		sendUiEvent(event);
	}

	Action1P<UiEvent> HostGmAdapter::getPostUiEventAction() {
		return bind(&HostGmAdapter::postUiEvent, this, placeholders::_1);
	}

	void HostGmAdapter::sendUiEvent(UiEvent event) {
		for (int i = 0; i < (int) sockets.size(); i++) {
			if (sockets[i] == nullptr) {
				continue;
			}
			Packet packet = packUiEvent(fakePlayer(event, i));
			if (sockets[i]->send(packet) != Socket::Done) {
				sockets[i]->disconnect();
				sockets[i] = nullptr;
				disconnectPlayer(i);
				cout << "packet not sent!\n";
			}
			else {
				cout << "packet sent!\n";
			}
		}
	}

	void HostGmAdapter::receiveCommand(TcpSocket& socket, int sourcePlayer) {
		Packet packet;
		socket.receive(packet);
		postCommand(setPlayer(unpackCommand(packet), sourcePlayer));
	}

	void HostGmAdapter::disconnectPlayer(int player) {
		postUiEvent(UiEvent(UiEvent::GameOverEvent(false, 0)));
	}

	Command HostGmAdapter::unpackCommand(Packet packet) {
		Int32 typeInt32;
		packet >> typeInt32;
		auto commandType = (Command::CommandType) typeInt32;
		if (commandType == Command::CommandType::TileOpen) {
			Int32 l;
			Int32 c;
			packet >> l >> c;
			return Command(Command::TileOpenCommand(l, c));
		}
		if (commandType == Command::CommandType::TileFlag) {
			Int32 l;
			Int32 c;
			packet >> l >> c;
			return Command(Command::TileFlagCommand(l, c));
		}
		if (commandType == Command::CommandType::TurnEnd) {
			return Command(Command::TurnEndCommand(0));
		}
		return Command::getInvalidCommand();
	}

	Packet HostGmAdapter::packUiEvent(UiEvent event) {
		Packet result;
		result << (Int32)event.eventType;

		if (event.eventType == UiEvent::UiEventType::TileReveal) {
			result << (Int32)event.tileRevealEvent.line << (Int32)event.tileRevealEvent.column
				<< (Int32)event.tileRevealEvent.neighbors;
		}
		if (event.eventType == UiEvent::UiEventType::TileFlag) {
			result << (Int32)event.tileFlagEvent.line << (Int32)event.tileFlagEvent.column
				<< (Uint8)event.tileFlagEvent.flagged << (Int32)event.tileFlagEvent.player;
		}
		if (event.eventType == UiEvent::UiEventType::RevealAccepted) {
		}
		if (event.eventType == UiEvent::UiEventType::GameOver) {
			result << (Int8)event.gameOverEvent.won << (Int32)event.gameOverEvent.player;
		}
		if (event.eventType == UiEvent::UiEventType::MineExplode) {
			result << (Int32)event.mineExplodeEvent.line << (Int32)event.mineExplodeEvent.column;
		}
		if (event.eventType == UiEvent::UiEventType::PlayerDead) {
			result << (Int32)event.playerDeadEvent.player;
		}
		if (event.eventType == UiEvent::UiEventType::TurnStart) {
			result << (Int32)event.turnStartEvent.player;
		}
		
		return result;
	}

	int transformPlayerId(int playerId, int targetPlayer);

	UiEvent HostGmAdapter::fakePlayer(UiEvent source, int player) {
		if (source.eventType == UiEvent::UiEventType::TileFlag) {
			source.tileFlagEvent.player = transformPlayerId(source.tileFlagEvent.player, player);
		}
		else if (source.eventType == UiEvent::UiEventType::TurnStart) {
			source.turnStartEvent.player = transformPlayerId(source.turnStartEvent.player, player);
		}
		else if (source.eventType == UiEvent::UiEventType::GameOver) {
			source.gameOverEvent.player = transformPlayerId(source.gameOverEvent.player, player);
		}
		else if (source.eventType == UiEvent::UiEventType::PlayerDead) {
			source.playerDeadEvent.player = transformPlayerId(source.playerDeadEvent.player, player);
		}

		return source;
	}

	Command HostGmAdapter::setPlayer(Command source, int player) {
		if (source.commandType == Command::CommandType::TileFlag) {
			source.tileFlagCommand.player = player;
		}
		if (source.commandType == Command::CommandType::TileOpen) {
			source.tileOpenCommand.player = player;
		}
		if (source.commandType == Command::CommandType::TurnEnd) {
			source.turnEndCommand.player = player;
		}

		return source;

	}

	int transformPlayerId(int playerId, int targetPlayer) {
		if (playerId == targetPlayer) {
			return 0;
		}
		return playerId + (int)(targetPlayer < playerId);
	}
}


