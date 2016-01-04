#pragma once
#include <SFGUI/Box.hpp>
#include "ScoreboardItem.h"

namespace mMp {
	using namespace sfg;
	using namespace std;
	class Scoreboard
	{
		vector<ScoreboardItem> items;

		Widget::Ptr widget;

	public:
		explicit Scoreboard(vector<string> names);

		void incrementScore(int player);
		void setPlayerDead(int player);
		void setActivePlayer(int activePlayer, int inactivePlayer, bool skipInactive);

		Widget::Ptr getWidget();
	};
}
