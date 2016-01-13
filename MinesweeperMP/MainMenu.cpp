#include "MainMenu.h"
#include "MainMenuUi.h"
#include "GameMenuNode.h"

namespace mMp
{
	MainMenu::MainMenu(Desktop& sfgDesktop, Action closeAction)
		: MenuNode(sfgDesktop, make_shared<MainMenuUi>(getPlaySpAction(), getPlayLocalMpAction(), closeAction,
			sfgDesktop)) {
	}

	GameSettings getSpGameSettings();
	GameSettings getLocalMpGameSettings();

	void MainMenu::playSp() {
		setChild(make_shared<GameMenuNode>(getSpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}

	void MainMenu::playLocalMp() {
		setChild(make_shared<GameMenuNode>(getLocalMpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}


	Action MainMenu::getPlaySpAction() {
		return bind(&MainMenu::playSp, this);
	}

	Action MainMenu::getPlayLocalMpAction() {
		return bind(&MainMenu::playLocalMp, this);
	}

	GameSettings getSpGameSettings() {
		return GameSettings(20, 100, false);
	}

	GameSettings getLocalMpGameSettings() {
		return GameSettings(20, 100, true, vector<string>({ "Player 1", "Player 2", "Player 3", "Player 4" }));
	}
}
