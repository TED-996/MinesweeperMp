#pragma once
#include "Command.h"
#include "Defines.h"
#include "UiEvent.h"
#include "Component.h"

namespace mMp {
	class GameManager : public Component
	{
		Action1P<UiEvent> postUiEventAction;
	public:
		explicit GameManager(Action1P<UiEvent> postUiEventAction);

		void postCommand(Command command);
	};
}
