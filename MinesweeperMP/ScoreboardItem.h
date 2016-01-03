#pragma once
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>

namespace mMp {
	using namespace sfg;
	using namespace std;
	class ScoreboardItem
	{
		Label::Ptr scoreLabel;

		Box::Ptr box;

	public:
		explicit ScoreboardItem(string name);

		void setScore(int score);
		
		Box::Ptr getBox();
	};

}
