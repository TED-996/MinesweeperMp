#include "MainMenu.h"
#include "MainMenuUi.h"
#include "GameMenuNode.h"

namespace mMp
{
	MainMenu::MainMenu(Desktop& sfgDesktop, Action closeAction)
		: MenuNode(sfgDesktop,
			make_shared<MainMenuUi>(bind(&MainMenu::onPlayPressed, this), closeAction, sfgDesktop)) {
	}

	GameSettings getSpGameSettings();
	GameSettings getMpGameSettings();

	void MainMenu::onPlayPressed() {
		setChild(make_shared<GameMenuNode>(getMpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}

	GameSettings getSpGameSettings() {
		return GameSettings(20, 100);
	}

	GameSettings getMpGameSettings() {
		return GameSettings(20, 20, true, true, false,
			vector<string>({"Player 1", "Player 2", "Player 3", "Player 4"}));
	}
}
