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
			if (socket != nullptr) {
				socket->disconnect();
			}
		}
		return false;
	}

	void ClientGmAdapter::update(float seconds) {
		Packet packet;
		if (socket != nullptr && socket->receive(packet) == Socket::Done) {
			postUiEventAction(unpackEvent(packet));
		}
	}

	Packet ClientGmAdapter::packCommand(Command command) {
		Packet result;
		result << (Int32)command.commandType;
		if (command.commandType == Command::CommandType::TileOpen) {
			result << (Int32)command.tileOpenCommand.line << (Int32)command.tileOpenCommand.column;
		}
		if (command.commandType == Command::CommandType::TileFlag) {
			result << (Int32)command.tileFlagCommand.line << (Int32)command.tileFlagCommand.column;
		}
		if (command.commandType == Command::CommandType::TurnEnd) {
		}

		return result;
	}

	UiEvent ClientGmAdapter::unpackEvent(Packet packet) {
		Int32 eventTypeInt32;
		packet >> eventTypeInt32;
		auto eventType = (UiEvent::UiEventType) eventTypeInt32;
		if (eventType == UiEvent::UiEventType::TileReveal) {
			Int32 line;
			Int32 column;
			Int32 neighbors;
			packet >> line >> column >> neighbors;
			return UiEvent(UiEvent::TileRevealEvent(line, column, neighbors));
		}
		if (eventType == UiEvent::UiEventType::TileFlag) {
			Int32 line;
			Int32 column;
			Uint8 flagged;
			Int32 player;
			packet >> line >> column >> flagged >> player;
			return UiEvent(UiEvent::TileFlagEvent(line, column, (flagged != 0), player));
		}
		if (eventType == UiEvent::UiEventType::RevealAccepted) {
		}
		if (eventType == UiEvent::UiEventType::GameOver) {
			Int8 won;
			Int32 player;
			packet >> won >> player;
			return UiEvent(UiEvent::GameOverEvent((won != 0), player));
		}
		if (eventType == UiEvent::UiEventType::MineExplode) {
			Int32 line;
			Int32 column;
			packet >> line >> column;
			return UiEvent(UiEvent::MineExplodeEvent(line, column));
		}
		if (eventType == UiEvent::UiEventType::PlayerDead) {
			Int32 player;
			packet >> player;
			return UiEvent(UiEvent::PlayerDeadEvent(player));
		}
		if (eventType == UiEvent::UiEventType::TurnStart) {
			Int32 player;
			packet >> player;
			return UiEvent(UiEvent::TurnStartEvent(player));
		}

		return UiEvent::getInvalidEvent();
	}
}
