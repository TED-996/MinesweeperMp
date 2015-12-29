#pragma once
#include <SFGUI/Widgets.hpp>
#include "Component.h"
#include "UiComponent.h"
#include "MainMenuUi.h"


namespace mMp {
	using namespace std;
	using namespace sfg;
	class MenuNode : public Component
	{
	protected:
		UiComponent::Ptr uiComponent;
		Component::Ptr childComponent;
		bool childActive;

		Desktop& sfgDesktop;


	public:
		explicit MenuNode(Desktop& sfgDesktop, UiComponent::Ptr uiComponent);

		void setChild(Component::Ptr newChild);
		void removeChild();

		virtual void draw(RenderTarget& target, RenderStates states) override;
		virtual bool handleEvent(Event event) override;
		virtual void update(float seconds) override;

	protected:
		Action getRemoveChildAction();
	private:
		void stashUi();
		void unstashUi();
	};
}
