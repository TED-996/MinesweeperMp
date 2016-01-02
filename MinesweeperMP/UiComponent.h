#pragma once
#include <SFGUI/Widgets.hpp>
#include "Component.h"

namespace mMp {
	using namespace sfg;
	class UiComponent : public Component
	{
	public:
		typedef std::shared_ptr<UiComponent> Ptr;
	
	private:
		bool initialized;
		bool disabled;
	protected:
		Desktop& desktop;
		sfg::Window::Ptr window;

	public:
		UiComponent(Desktop& desktop);
		~UiComponent();

		void init();
		void reset();
		void disable();
		void enable();

		void update(float seconds) override;

	protected:
		virtual void initWindow() = 0;
	};
}
