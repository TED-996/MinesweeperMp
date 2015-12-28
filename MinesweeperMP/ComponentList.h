#pragma once
#include <vector>
#include "Component.h"
#include <memory>

namespace mMp {
	using namespace std;
	class ComponentList : public Component
	{
	public:
		vector<shared_ptr<Component>> components;

		void add(shared_ptr<Component> c);
		bool remove(shared_ptr<Component> c);
		void clear();

		void draw(RenderTarget& target, RenderStates states) override;
		bool handleEvent(Event event) override;
		void update(float seconds) override;
	};
}
