#pragma once

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

namespace mMp {
	using namespace sf;
	using namespace sfg;

	class Application
	{
		RenderWindow renderWindow;
		SFGUI sfGui;
		Desktop desktop;

		Clock tickClock;

		void Update();
		void Draw();
		void HandleEvents();
	public:
		Application();
		~Application();

		void Run();
	};
}
