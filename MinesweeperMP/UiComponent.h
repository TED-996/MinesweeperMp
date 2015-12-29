#pragma once
#include <SFGUI/Widgets.hpp>
#include "Component.h"

namespace mMp {
	using namespace sfg;
	class UiComponent : public Component
	{
		Desktop& desktop;

		//TODO: Make a way to hide without obliterating.
		bool initialized;
	protected:
		sfg::Window::Ptr window;

	public:
		UiComponent(Desktop& desktop);
		~UiComponent();

		void update(float seconds) override;

	protected:
		virtual void initWindow() = 0;
	};
}
