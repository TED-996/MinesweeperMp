#pragma once
#include "UiComponent.h"
#include "MainMenuUi.h"
#include "UiEvent.h"
#include "Command.h"

namespace mMp {

	class GameUi : public UiComponent
	{
		Action closeAction;
		Action1P<Command> postCommandAction;

	public:
		GameUi(Action1P<Command> postCommandAction, Action closeAction, Desktop& desktop);

		void postUiEvent(UiEvent event);
			
	protected:
		void initWindow() override;
	};
}
