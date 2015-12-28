#include "ComponentList.h"

namespace mMp
{
	void ComponentList::add(shared_ptr<Component> c) {
		components.push_back(c);
	}

	bool ComponentList::remove(shared_ptr<Component> c) {
		for (auto it = components.begin(); it != components.end(); ++it) {
			if (*it == c) {
				components.erase(it);
				return true;
			}
		}
		return false;
	}

	void ComponentList::clear() {
		components.clear();
	}

	void ComponentList::draw(RenderTarget& target, RenderStates states) {
		for(auto c : components) {
			c->draw(target, states);
		}
	}

	bool ComponentList::handleEvent(Event event) {
		for (auto c : components) {
			if (c->handleEvent(event)) {
				return true;
			}
		}
		return false;
	}

	void ComponentList::update(float seconds) {
		for (auto c : components) {
			c->update(seconds);
		}
	}
}
