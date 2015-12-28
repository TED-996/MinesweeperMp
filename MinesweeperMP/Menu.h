#pragma once
#include "Component.h"

namespace mMp {
	class Menu : Component
	{
		std::vector<Component> components;
	public:
		void draw(RenderTarget& target, RenderStates states) override;
		bool handleEvent(Event event) override;
		void update(float seconds) override;
	};
}
