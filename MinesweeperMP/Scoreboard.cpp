#include "Scoreboard.h"

namespace mMp {
	Scoreboard::Scoreboard(vector<string> names) {
		items = vector<ScoreboardItem>();
		box = Box::Create(Box::Orientation::VERTICAL, 2);
		for (auto name : names) {
			ScoreboardItem item(name);
			items.push_back(item);
			box->Pack(item.getBox());
		}
	}

	void Scoreboard::setScore(int player, int score) {
		items[player].setScore(score);
	}

	Box::Ptr Scoreboard::getBox() {
		return box;
	}
}
