#include "MainMenu.h"
#include "MainMenuUi.h"
#include "GameMenuNode.h"

namespace mMp
{
	MainMenu::MainMenu(Desktop& sfgDesktop, Action closeAction)
		: MenuNode(sfgDesktop, make_shared<MainMenuUi>(getPlaySpAction(), getPlayLocalMpAction(),
			getUpdateSettingsAction(), closeAction, sfgDesktop)), gameSettings(0, 0) {
	}

	void MainMenu::playSp() {
		gameSettings.isMp = false;
		setChild(make_shared<GameMenuNode>(gameSettings, getRemoveChildAction(), sfgDesktop));
	}

	void MainMenu::playLocalMp() {
		gameSettings.isMp = false;
		gameSettings.names = vector<string>({ "Player 1", "Player 2", "Player 3", "Player 4" });
		setChild(make_shared<GameMenuNode>(gameSettings, getRemoveChildAction(), sfgDesktop));
	}


	void MainMenu::updateSettings(GameSettings newSettings) {
		gameSettings.boardSize = newSettings.boardSize;
		gameSettings.mineCount = newSettings.mineCount;
	}

	Action MainMenu::getPlaySpAction() {
		return bind(&MainMenu::playSp, this);
	}

	Action MainMenu::getPlayLocalMpAction() {
		return bind(&MainMenu::playLocalMp, this);
	}

	Action1P<GameSettings> MainMenu::getUpdateSettingsAction() {
		return bind(&MainMenu::updateSettings, this, placeholders::_1);
	}
}
