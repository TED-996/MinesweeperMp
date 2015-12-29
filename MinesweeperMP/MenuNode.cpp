#include "MenuNode.h"

namespace mMp {
	void MenuNode::draw(RenderTarget& target, RenderStates states) {
		rootComponent->draw(target, states);
	}

	bool MenuNode::handleEvent(Event event) {
		if (rootComponent->handleEvent(event)) {
			return true;
		}
		return false;
	}

	void MenuNode::update(float seconds) {
		rootComponent->update(seconds);
	}
}