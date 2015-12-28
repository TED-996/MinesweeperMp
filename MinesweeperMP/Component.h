#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "EventHandler.h"
#include "Drawable.h"

using namespace sf;

namespace mMp {
	class Component : Updateable, Drawable, EventHandler
	{
	public:
		virtual void draw(RenderTarget& target, RenderStates states) override = 0;
		virtual bool handleEvent(Event event) override = 0;
		virtual void update(float seconds) override = 0;
	};
}