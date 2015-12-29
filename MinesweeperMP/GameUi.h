#pragma once
#include "UiComponent.h"
#include "MainMenuUi.h"

namespace mMp {
	class GameUi : public UiComponent
	{
		Action closeAction;

	public:
		explicit GameUi(Action closeAction, Desktop& desktop);

	protected:
		void initWindow() override;
	};
}
