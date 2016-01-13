﻿#pragma once
#include "UiComponent.h"
#include "Defines.h"
#include "GameSettings.h"

namespace mMp {
	using namespace std;
	class MainMenuUi : public UiComponent
	{
		Action playSpAction;
		Action playLocalMpAction;
		Action1P<GameSettings> updateSettingsAction;
		Action exitAction;

		Label::Ptr boardSizeLabel;
		Label::Ptr mineCountLabel;
		Scale::Ptr boardSizeScale;
		Scale::Ptr mineCountScale;

		GameSettings gameSettings;
		
	public:
		MainMenuUi(Action playSpAction, Action playLocalMpAction, Action1P<GameSettings> updateSettingsAction,
			Action exitAction, Desktop& desktop);

	protected:
		void initWindow() override;
	private:
		void updateBoardSize();
		void updateMineCount();
	};
}
