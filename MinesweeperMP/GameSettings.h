#pragma once
#include <string>
#include <vector>

namespace mMp {
	using namespace std;
	struct GameSettings
	{
		int boardSize;
		int mineCount;
		bool isMp;
		bool isLocal;
		bool isRemote;
		vector<string> names;

		GameSettings(int boardSize, int mineCount, bool isMp = false, bool isLocal = true, bool isRemote = false,
			vector<string> names = vector<string>());
	};
}
