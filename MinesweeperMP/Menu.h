#pragma once
#include <SFGUI/Widgets.hpp>
#include "Component.h"
#include "ComponentList.h"


namespace mMp {
	using namespace sfg;
	class Menu : public Component
	{
	protected:
		ComponentList componentList;
		sfg::Window::Ptr window;

		virtual void initWindow() = 0;
	public:
		virtual void loadUi(Desktop& desktop);
		virtual void unloadUi(Desktop& desktop);

		virtual void draw(RenderTarget& target, RenderStates states) override;
		virtual bool handleEvent(Event event) override;
		virtual void update(float seconds) override;
	};
}
