#pragma once
#include "UiComponent.h"
#include "Defines.h"

namespace mMp {
	using namespace std;
	class MainMenuUi : public UiComponent
	{
		Action playAction;
		Action exitAction;
		
	public:
		explicit MainMenuUi(Action playAction, Action exitAction, Desktop& desktop);

	protected:
		void initWindow() override;
	};
}
