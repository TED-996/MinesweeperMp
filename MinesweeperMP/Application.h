#pragma once

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "Menu.h"
#include "MainMenu.h"

namespace mMp {
	using namespace sf;
	using namespace sfg;

	class Application
	{
		RenderWindow renderWindow;
		SFGUI sfGui;
		Desktop desktop;

		Clock tickClock;

		shared_ptr<MainMenu> mainMenu;

		void update();
		void draw();
		void handleEvents();
	public:
		Application();
		
		void init();
		void run();
	};
}
