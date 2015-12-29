#pragma once
#include <SFGUI/Widgets.hpp>
#include "MenuNode.h"
#include "MainMenuUi.h"

namespace mMp {
	using namespace sfg;
	class MainMenu : public MenuNode
	{
		void onPlayPressed();

	public:
		MainMenu(Desktop& sfgDesktop, Action closeAction);
	};
}
