#pragma once
#include "UiComponent.h"
#include "Defines.h"

namespace mMp {
	using namespace std;
	class MainMenuUi : public UiComponent
	{
		Action playSpAction;
		Action playLocalMpAction;
		Action exitAction;
		
	public:
		MainMenuUi(Action playSpAction, Action playLocalMpAction, Action exitAction, Desktop& desktop);

	protected:
		void initWindow() override;
	};
}
