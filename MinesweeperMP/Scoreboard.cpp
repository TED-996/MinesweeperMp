#include "Scoreboard.h"
#include <SFGUI/Frame.hpp>

namespace mMp {
	Scoreboard::Scoreboard(vector<string> names) {
		items = vector<ScoreboardItem>();
		auto box = Box::Create(Box::Orientation::VERTICAL, 2);
		for (auto name : names) {
			ScoreboardItem item(name);
			items.push_back(item);
			box->Pack(item.getWidget());
		}
		auto frame = Frame::Create("Scroreboard");

		frame->Add(box);

		widget = frame;
	}

	void Scoreboard::incrementScore(int player) {
		items[player].incrementScore();
	}

	void Scoreboard::setPlayerDead(int player) {
		items[player].setPlayerDead();
	}

	void Scoreboard::setActivePlayer(int activePlayer, int inactivePlayer, bool skipInactive) {
		if (!skipInactive && activePlayer != inactivePlayer) {
			items[inactivePlayer].setPlayerInactive();
		}
		items[activePlayer].setPlayerActive();
	}

	Widget::Ptr Scoreboard::getWidget() {
		return widget;
	}

}
