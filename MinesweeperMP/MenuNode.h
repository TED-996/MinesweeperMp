#pragma once
#include <SFGUI/Widgets.hpp>
#include "Component.h"


namespace mMp {
	using namespace sfg;
	class MenuNode : public Component
	{
	protected:
		Component::Ptr rootComponent;
		Desktop& sfgDesktop;

	public:
		explicit MenuNode(Desktop& sfgDesktop)
			: sfgDesktop(sfgDesktop) {
		}

		virtual void changeComponent(Component::Ptr newComponent);
		virtual void draw(RenderTarget& target, RenderStates states) override;
		virtual bool handleEvent(Event event) override;
		virtual void update(float seconds) override;
	};
}
