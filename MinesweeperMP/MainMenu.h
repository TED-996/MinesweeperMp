#pragma once
#include <SFGUI/Widgets.hpp>
#include "Menu.h"

namespace mMp {
	using namespace sfg;
	class MainMenu : public Menu
	{
		function<void()> closeFunction;

		void onPlayClick();
		void onExitClick();

	protected:
		void initWindow() override;

	public:
		MainMenu(function<void()> newCloseFunction);
	};
}
