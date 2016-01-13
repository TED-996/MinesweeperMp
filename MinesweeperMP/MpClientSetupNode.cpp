#include "MpClientSetupNode.h"
#include "MpClientSetupUi.h"
#include "GameMenuNode.h"

namespace mMp {
	MpClientSetupNode::MpClientSetupNode(GameSettings gameSettings, Action backAction, Desktop& sfgDesktop)
		: MenuNode(sfgDesktop,
			make_shared<MpClientSetupUi>(sfgDesktop, backAction, getSetNameAction(), getSelectServerAction())),
		gameSettings(gameSettings), backAction(backAction) {
		customUi = dynamic_pointer_cast<MpClientSetupUi>(uiComponent);
		connected = false;

		tcpSocket = make_shared<TcpSocket>();

		udpSocket.bind(ct::TcpPort + 1);
		udpSocket.setBlocking(false);
	}

	bool MpClientSetupNode::handleEvent(Event event) {
		if (event.type == Event::Closed) {
			//If the socket is connected
			if (tcpSocket->getRemoteAddress() != IpAddress::None) {
				tcpSocket->disconnect();
			}
		}
		return false;
	}

	void MpClientSetupNode::update(float seconds) {
		if (!connected) {
			receiveUdpBroadcast();
		}
		else{
			receiveTcpSettings();
		}
	}

	void MpClientSetupNode::receiveUdpBroadcast() {
		Packet packet;
		IpAddress address = IpAddress::Broadcast;
		unsigned short port = ct::UdpPort;
		if (udpSocket.receive(packet, address, port) == Socket::Done) {
			string name;
			packet >> name;
			ipAddresses.push_back(address);
			customUi->addServer(name);
		}
	}

	void MpClientSetupNode::setName(string name) {
		gameSettings.names.push_back(name);
	}

	void MpClientSetupNode::selectServer(int index) {
		createSocket(ipAddresses[index]);
	}

	void MpClientSetupNode::createSocket(IpAddress ipAddress) {
		if (tcpSocket->connect(ipAddress, ct::TcpPort) !=  Socket::Done) {
			cout << "cannot connect\n";
			backAction();
		}
		gameSettings.sockets.push_back(tcpSocket);
	}

	void MpClientSetupNode::receiveTcpSettings() {
		Packet packet;
		if (tcpSocket->receive(packet) == Socket::Done) {
			Int32 boardSize;
			Int32 mineCount;
			Int32 playerCount;
			//Packet layout: [BoardSize][MineCount][NameNumber][Name1][Name2] ... 
			packet >> boardSize >> mineCount >> playerCount;
			for (int i = 0; i < playerCount; i++) {
				string str;
				packet >> str;
				gameSettings.names.push_back(str);
			}
			setChild(make_shared<GameMenuNode>(gameSettings, backAction, sfgDesktop));
		}
	}

	Action1P<int> MpClientSetupNode::getSelectServerAction() {
		return bind(&MpClientSetupNode::selectServer, this, placeholders::_1);
	}

	Action1P<string> MpClientSetupNode::getSetNameAction() {
		return bind(&MpClientSetupNode::setName, this, placeholders::_1);
	}
}
