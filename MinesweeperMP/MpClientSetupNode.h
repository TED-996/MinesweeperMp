#pragma once
#include <SFML/Network.hpp>
#include "MenuNode.h"
#include "MpClientSetupUi.h"
#include "GameSettings.h"

namespace mMp {
	using namespace sfg;
	class MpClientSetupNode : public MenuNode
	{
		vector<IpAddress> ipAddresses;

		shared_ptr<TcpSocket> tcpSocket;
		UdpSocket udpSocket;

		shared_ptr<MpClientSetupUi> customUi;

		GameSettings gameSettings;

		bool connected;
	public:
		Action backAction;
	public:
		MpClientSetupNode(GameSettings gameSettings, Action backAction, Desktop& sfgDesktop);

		bool handleEvent(Event event) override;
		void update(float seconds) override;
	private:
		void receiveUdpBroadcast();
		void setName(string name);
		void selectServer(int index);
		void createSocket(IpAddress ipAddress);
		void receiveTcpSettings();


		Action1P<int> getSelectServerAction();
		Action1P<string> getSetNameAction();
	};
}
