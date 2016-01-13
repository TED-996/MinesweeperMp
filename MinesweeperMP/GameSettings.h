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
		vector<string> names;

		GameSettings(int boardSize, int mineCount, bool isMp = false, vector<string> names = vector<string>());
	};
}
