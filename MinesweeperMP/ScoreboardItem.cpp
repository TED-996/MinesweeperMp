#include "ScoreboardItem.h"
#include <SFGUI/Frame.hpp>

namespace mMp {
	using namespace sf;

	ScoreboardItem::ScoreboardItem(string name) {
		score = 0;

		auto box = Box::Create(Box::Orientation::HORIZONTAL, 2);
		
		auto nameLabel = Label::Create(name);
		nameLabel->SetAlignment(Vector2f(0.0f, 0.5f));

		scoreLabel = Label::Create();
		scoreLabel->SetText("0");
		scoreLabel->SetRequisition(Vector2f(40.0f, 0.0f));
		scoreLabel->SetAlignment(Vector2f(1.0f, 0.5f));
			
		box->Pack(scoreLabel, false, false);
		box->PackStart(nameLabel, true, true);

		widget = Frame::Create();
		widget->Add(box);
		widget->SetClass("PlayerInactive");
	}

	Widget::Ptr ScoreboardItem::getWidget() {
		return widget;
	}

	void ScoreboardItem::incrementScore() {
		score++;
		scoreLabel->SetText(to_string(score));
	}

	void ScoreboardItem::setPlayerDead() {
		widget->SetClass("PlayerDead");
	}

	void ScoreboardItem::setPlayerActive() {
		widget->SetClass("PlayerActive");
	}

	void ScoreboardItem::setPlayerInactive() {
		widget->SetClass("PlayerInactive");
	}
}
