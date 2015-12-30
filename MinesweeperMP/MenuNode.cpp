#include "MenuNode.h"

namespace mMp {
	MenuNode::MenuNode(Desktop& sfgDesktop, UiComponent::Ptr uiComponent)
		: uiComponent(uiComponent), sfgDesktop(sfgDesktop) {
		childActive = false;
		uiComponent->init();

		childComponent = uiComponent;
	}

	void MenuNode::setChild(Component::Ptr newChild) {
		if (!childActive) {
			stashUi();
		}
		childComponent = newChild;
		childActive = true;
	}

	void MenuNode::removeChild() {
		unstashUi();
		childActive = false;
	}

	Action MenuNode::getRemoveChildAction() {
		return bind(&MenuNode::removeChild, this);
	}

	void MenuNode::stashUi() {
		uiComponent->disable();
	}

	void MenuNode::unstashUi() {
		uiComponent->reset();
		uiComponent->enable();

		childComponent = uiComponent;
	}

	void MenuNode::draw(RenderTarget& target, RenderStates states) {
		childComponent->draw(target, states);
	}

	bool MenuNode::handleEvent(Event event) {
		if (childComponent->handleEvent(event)) {
			return true;
		}
		return false;
	}

	void MenuNode::update(float seconds) {
		childComponent->update(seconds);
	}
}
