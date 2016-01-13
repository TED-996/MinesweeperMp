#include "MpHostSetupNode.h"
#include "MpHostSetupUi.h"
#include "GameMenuNode.h"

namespace mMp
{
	MpHostSetupNode::MpHostSetupNode(GameSettings gameSettings, Action closeAction, Desktop& sfgDesktop)
		: MenuNode(sfgDesktop,
			make_shared<MpHostSetupUi>(sfgDesktop, closeAction, getCreateServerAction(), getStartGameAction())), 
			closeAction(closeAction), gameSettings(gameSettings) {
		serverWaiting = false;
		customUiComponent = dynamic_pointer_cast<MpHostSetupUi>(uiComponent);
		
		listener.setBlocking(false);
		listener.listen(ct::TcpPort);
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
		serverWaiting = true;
	}

	void MpHostSetupNode::startGame() {
		serverWaiting = false;
		sendGameSettings();
		setChild(make_shared<GameMenuNode>(gameSettings, closeAction, sfgDesktop));
	}

	void MpHostSetupNode::sendGameSettings() {
		for (int i = 1; i < (int)gameSettings.sockets.size(); i++) {
			Packet packet;
			//Packet layout: [BoardSize][MineCount][NameNumber][Name1][Name2] ... 
			packet << (Int32)gameSettings.boardSize << (Int32)gameSettings.mineCount
				<< (Int32)gameSettings.names.size() - 1;

			for (int j = 0; j < gameSettings.names.size(); j++) {
				if (j != i) {
					packet << gameSettings.names[i];
				}
			}

			if (gameSettings.sockets[i]->send(packet) != Socket::Done) {
				closeSockets();
				closeAction();
				return;
			}
		}
	}

	bool MpHostSetupNode::handleEvent(Event event) {
		if (event.type == Event::Closed) {
			closeSockets();
		}
		return MenuNode::handleEvent(event);
	}

	void MpHostSetupNode::update(float seconds) {
		MenuNode::update(seconds);
		if (!serverWaiting) {
			return;
		}

		shared_ptr<TcpSocket> socket = make_shared<TcpSocket>();
		if (listener.accept(*socket) == Socket::Done) {
			gameSettings.sockets.push_back(socket);
			//TODO: get name...
			string name = "Player " + to_string(gameSettings.sockets.size() + 1);
			gameSettings.names.push_back(name);
			customUiComponent->addName(name);
		}
		if (broadcastTimer.getElapsedTime() > sf::seconds(5)) {
			broadcastHost();
			broadcastTimer.restart();
		}
	}

	void MpHostSetupNode::broadcastHost() {
		UdpSocket socket;
		if (socket.bind(ct::UdpPort) != Socket::Done) {
			cout << "Could not bind the socket to broadcast! :(\n";
			return;
		}
		Packet packet;

		packet << gameSettings.names[0];
		if (socket.send(packet, IpAddress::Broadcast, ct::UdpPort) != Socket::Done) {
			cout << "could not broadcast! :(\n";
			return;
		}
	}

	void MpHostSetupNode::closeSockets() {
		for (auto socket : gameSettings.sockets) {
			if (socket != nullptr) {
				socket->disconnect();
			}
		}
	}
}
