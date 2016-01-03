#pragma once
#include <SFGUI/Box.hpp>
#include "ScoreboardItem.h"

namespace mMp {
	using namespace sfg;
	using namespace std;
	class Scoreboard
	{
		vector<ScoreboardItem> items;

		Box::Ptr box;

	public:
		explicit Scoreboard(vector<string> names);

		void setScore(int player, int score);

		Box::Ptr getBox();
	};
}
