#pragma once
#include <string>
#include <vector>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>

namespace mMp {
	using namespace std;
	using namespace sf;

	struct GameSettings
	{
		int boardSize;
		int mineCount;
		bool isMp;
		bool isLocal;
		bool isRemote;
		vector<string> names;
		vector<shared_ptr<TcpSocket> > sockets;

		GameSettings(int boardSize, int mineCount, bool isMp = false, bool isLocal = true, bool isRemote = false,
			vector<string> names = vector<string>(),
			vector<shared_ptr<TcpSocket> > sockets = vector<shared_ptr<TcpSocket> >());
	};
}
