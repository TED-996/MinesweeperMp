#include "UiComponent.h"

namespace mMp
{
	UiComponent::UiComponent(Desktop& desktop)
		: desktop(desktop) {
		window = sfg::Window::Create();
		desktop.Add(window);

		initialized = false;
		disabled = false;
	}

	UiComponent::~UiComponent() {
		desktop.Remove(window);
		window.reset();
	}

	void UiComponent::init() {
		if (!initialized) {
			initWindow();
			initialized = true;
		}
	}

	void UiComponent::reset() {
		if (!initialized) {
			init();
		}
		else {
			window->RemoveAll();
			window->SetAllocation(sf::FloatRect(0, 0, 0, 0));
			window->SetStyle(Style::Default);
			window->SetTitle("");
			//TODO: Add more properties as necessary.

			initWindow();
		}
	}

	void UiComponent::disable() {
		if (!disabled) {
			desktop.Remove(window);
			window->Show(false);
			disabled = true;
		}
	}

	void UiComponent::enable() {
		init();
		if (disabled) {
			desktop.Add(window);
			window->Show(true);
			disabled = false;
		}
	}

	void UiComponent::update(float seconds) {
		if (!initialized) {
			initWindow();
			initialized = true;
		}
	}
}


