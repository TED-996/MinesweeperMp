#include "MainMenu.h"
#include "MainMenuUi.h"

namespace mMp
{
	MainMenu::MainMenu(Desktop& sfgDesktop, Action closeAction)
		: MenuNode(sfgDesktop) {
		rootComponent = make_shared<MainMenuUi>(bind(&MainMenu::onPlayPressed, this), closeAction, sfgDesktop);
	}

	void MainMenu::onPlayPressed() {
	}
}
