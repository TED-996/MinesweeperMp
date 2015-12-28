#include "Application.h"
#include "Constants.h"

namespace mMp {

	Application::Application() {
	}

	void Application::init() {
		renderWindow.create(VideoMode(ct::WindowWidth, ct::WindowHeight), "MinesweeperMP");
		renderWindow.resetGLStates();

		mainMenu = make_shared<MainMenu>([&]() { renderWindow.close(); });
		mainMenu->loadUi(desktop);

		tickClock.restart();
	}

	void Application::run() {
		while (renderWindow.isOpen()) {
			handleEvents();

			update();
			draw();
		}
	}

	void Application::handleEvents() {
		Event event;
		while(renderWindow.pollEvent(event)) {
			desktop.HandleEvent(event);
			mainMenu->handleEvent(event);

			if (event.type == Event::Closed) {
				renderWindow.close();
			}
		}
	}

	void Application::update() {
		float tickSeconds = tickClock.restart().asSeconds();
		desktop.Update(tickSeconds);

		mainMenu->update(tickSeconds);
	}

	void Application::draw() {
		renderWindow.clear();
		sfGui.Display(renderWindow);

		mainMenu->draw(renderWindow, RenderStates());
		
		renderWindow.display();
	}
}
