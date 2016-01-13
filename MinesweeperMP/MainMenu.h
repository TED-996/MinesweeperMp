#pragma once
#include <SFGUI/Widgets.hpp>
#include "MenuNode.h"
#include "MainMenuUi.h"

namespace mMp {
	using namespace sfg;
	class MainMenu : public MenuNode
	{
		GameSettings gameSettings;
	public:
		MainMenu(Desktop& sfgDesktop, Action closeAction);
	private:

		void playSp();
		void playLocalMp();
		void updateSettings(GameSettings newSettings);

		Action getPlaySpAction();
		Action getPlayLocalMpAction();
		Action1P<GameSettings> getUpdateSettingsAction();
	};
}
