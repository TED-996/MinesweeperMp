#include "MainMenu.h"
#include "MainMenuUi.h"
#include "GameMenuNode.h"
#include "MpHostSetupNode.h"
#include "MpClientSetupNode.h"

namespace mMp
{
	MainMenu::MainMenu(Desktop& sfgDesktop, Action closeAction)
		: MenuNode(sfgDesktop, make_shared<MainMenuUi>(getPlaySpAction(), getPlayLocalMpAction(), getHostMpAction(),
			getJoinMpAction(), closeAction, sfgDesktop)) {
	}

	GameSettings getSpGameSettings();
	GameSettings getLocalMpGameSettings();
	GameSettings getHostMpGameSettings();
	GameSettings getJoinMpGameSettings();

	void MainMenu::playSp() {
		setChild(make_shared<GameMenuNode>(getSpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}

	void MainMenu::playLocalMp() {
		setChild(make_shared<GameMenuNode>(getLocalMpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}

	void MainMenu::hostMp() {
		setChild(make_shared<MpHostSetupNode>(getHostMpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}

	void MainMenu::joinMp() {
		setChild(make_shared<MpClientSetupNode>(getJoinMpGameSettings(), getRemoveChildAction(), sfgDesktop));
	}


	Action MainMenu::getPlaySpAction() {
		return bind(&MainMenu::playSp, this);
	}

	Action MainMenu::getPlayLocalMpAction() {
		return bind(&MainMenu::playLocalMp, this);
	}

	Action MainMenu::getHostMpAction() {
		return bind(&MainMenu::hostMp, this);
	}

	Action MainMenu::getJoinMpAction() {
		return bind(&MainMenu::joinMp, this);
	}

	GameSettings getSpGameSettings() {
		return GameSettings(20, 100, false);
	}

	GameSettings getLocalMpGameSettings() {
		return GameSettings(20, 100, true, true, false,
			vector<string>({ "Player 1", "Player 2", "Player 3", "Player 4" }));
	}

	GameSettings getHostMpGameSettings() {
		return GameSettings(20, 100, true, false, false);
	}

	GameSettings getJoinMpGameSettings() {
		return GameSettings(20, 100, true, false, true);
	}
}
