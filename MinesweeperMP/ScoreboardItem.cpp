#include "ScoreboardItem.h"

namespace mMp {
	ScoreboardItem::ScoreboardItem(string name) {
		box = Box::Create(Box::Orientation::HORIZONTAL, 2);
		
		auto nameLabel = Label::Create(name);
		scoreLabel = Label::Create("0");

		box->Pack(scoreLabel, false, false);
		box->PackStart(nameLabel, true, true);
	}

	void ScoreboardItem::setScore(int score) {
		scoreLabel->SetText(to_string(score));
	}

	Box::Ptr ScoreboardItem::getBox() {
		return box;
	}
}
