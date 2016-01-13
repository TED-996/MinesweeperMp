﻿#pragma once
#include <SFGUI/Widgets.hpp>
#include "MenuNode.h"
#include "MainMenuUi.h"

namespace mMp {
	using namespace sfg;
	class MainMenu : public MenuNode
	{
	public:
		MainMenu(Desktop& sfgDesktop, Action closeAction);
	private:

		void playSp();
		void playLocalMp();

		Action getPlaySpAction();
		Action getPlayLocalMpAction();
	};
}
