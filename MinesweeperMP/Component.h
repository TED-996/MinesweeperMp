#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace mMp {
	using namespace sf;
	class Component
	{
	public:
		typedef std::shared_ptr<Component> Ptr;

		virtual ~Component() {
		}

		// Draw the component on the screen.
		virtual void draw(RenderTarget& target, RenderStates states) {
		}

		// Handle a particular event. If the event has been completely handled and this should stop, return true.
		virtual bool handleEvent(Event event) {
			return false;
		}

		// Update the component.
		virtual void update(float seconds) {
		}
	};
}