#pragma once
#include <SFML/Graphics.hpp>

namespace mMp
{
	using namespace sf;

	class EventHandler {
	public:
		virtual bool handleEvent(Event event);
	};
}
