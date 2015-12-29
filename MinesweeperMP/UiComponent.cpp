#include "UiComponent.h"

namespace mMp
{
	UiComponent::UiComponent(Desktop& desktop)
		: desktop(desktop) {
		window = sfg::Window::Create();
		desktop.Add(window);

		initialized = false;
	}

	UiComponent::~UiComponent() {
		desktop.Remove(window);
		window.reset();
	}

	void UiComponent::update(float seconds) {
		if (!initialized) {
			initWindow();
			initialized = true;
		}
	}
}


