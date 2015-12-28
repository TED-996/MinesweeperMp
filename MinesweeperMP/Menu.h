#pragma once
#include "Component.h"
#include "ComponentList.h"

namespace mMp {
	class Menu : Component
	{
		ComponentList componentList;
	public:
		void draw(RenderTarget& target, RenderStates states) override;
		bool handleEvent(Event event) override;
		void update(float seconds) override;
	};
}
