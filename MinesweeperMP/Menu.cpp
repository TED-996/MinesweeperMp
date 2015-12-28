#include "Menu.h"

namespace mMp {
	void Menu::loadUi(Desktop& desktop) {
		initWindow();
		desktop.Add(window);
	}

	void Menu::unloadUi(Desktop& desktop) {
		desktop.Remove(window);
		window.reset();
	}

	void Menu::draw(RenderTarget& target, RenderStates states) {
		componentList.draw(target, states);
	}

	bool Menu::handleEvent(Event event) {
		if (componentList.handleEvent(event)) {
			return true;
		}
		return false;
	}

	void Menu::update(float seconds) {
		componentList.update(seconds);
	}
}