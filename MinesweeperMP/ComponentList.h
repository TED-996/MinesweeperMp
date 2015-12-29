#pragma once
#include <vector>
#include "Component.h"

namespace mMp {
	using namespace std;
	class ComponentList : public Component
	{
	public:
		vector<Component::Ptr> components;

		void add(Component::Ptr c);
		bool remove(Component::Ptr c);
		void clear();

		void draw(RenderTarget& target, RenderStates states) override;
		bool handleEvent(Event event) override;
		void update(float seconds) override;
	};
}
