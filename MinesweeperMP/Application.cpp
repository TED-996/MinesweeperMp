#include "Application.h"

namespace mMp {
	Application::Application() {
		renderWindow.create(VideoMode(800, 600), "MinesweeperMP");

		tickClock.restart();
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (renderWindow.isOpen()) {
			HandleEvents();

			Update();
			Draw();
		}
	}

	void Application::HandleEvents() {
		Event event;
		while(renderWindow.pollEvent(event)) {
			desktop.HandleEvent(event);

			if (event.type == Event::Closed) {
				renderWindow.close();
			}
		}
	}

	void Application::Update() {
		float tickSeconds = tickClock.restart().asSeconds();
		desktop.Update(tickSeconds);

	}

	void Application::Draw() {
		renderWindow.clear();
		sfGui.Display(renderWindow);
		
		renderWindow.display();
	}
}
