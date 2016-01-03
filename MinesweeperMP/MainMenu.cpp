#include "MainMenu.h"
#include "MainMenuUi.h"
#include "GameMenuNode.h"

namespace mMp
{
	MainMenu::MainMenu(Desktop& sfgDesktop, Action closeAction)
		: MenuNode(sfgDesktop,
			make_shared<MainMenuUi>(bind(&MainMenu::onPlayPressed, this), closeAction, sfgDesktop)) {
	}

	void MainMenu::onPlayPressed() {
		setChild(make_shared<GameMenuNode>(GameSettings(20, 100), getRemoveChildAction(), sfgDesktop));
	}
}
