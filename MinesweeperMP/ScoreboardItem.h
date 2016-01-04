#pragma once
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Frame.hpp>

namespace mMp {
	using namespace sfg;
	using namespace std;
	class ScoreboardItem
	{
		Label::Ptr scoreLabel;
		int score;

		Frame::Ptr widget;

	public:
		explicit ScoreboardItem(string name);

		void incrementScore();
		void setPlayerDead();
		void setPlayerActive();
		void setPlayerInactive();

		Widget::Ptr getWidget();
	};

}
