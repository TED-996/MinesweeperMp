#include "MainMenuUi.h"

namespace mMp
{
	MainMenuUi::MainMenuUi(Action playSpAction, Action playLocalMpAction,
		Action1P<GameSettings> updateSettingsAction, Action exitAction, Desktop& desktop)
		: UiComponent(desktop), playSpAction(playSpAction), playLocalMpAction(playLocalMpAction),
		updateSettingsAction(updateSettingsAction), exitAction(exitAction), gameSettings(0, 0) {
	}

	extern Alignment::Ptr createAlignment(Widget::Ptr widget, Vector2f alignment,
		Vector2f scale = Vector2f(1.0f, 1.0f));

	void MainMenuUi::initWindow() {
		window->SetStyle(Style::Fullscreen);
		window->SetRequisition(Vector2f((float) ct::WindowWidth, (float) ct::WindowHeight));

		auto mMpLabel = Label::Create("Minesweeper: Multiplayer Edition");
		mMpLabel->SetAlignment(Vector2f(0.5f, 0.5f));
		mMpLabel->SetClass("MMpLabel");

		auto playSpButton = Button::Create("Play Singleplayer");
		playSpButton->GetSignal(Widget::OnLeftClick).Connect(playSpAction);
		auto playLocalMpButton = Button::Create("Play Local Multiplayer");
		playLocalMpButton->GetSignal(Widget::OnLeftClick).Connect(playLocalMpAction);

		auto exitButton = Button::Create("Exit");
		exitButton->GetSignal(Widget::OnLeftClick).Connect(exitAction);

		auto mainBox = Box::Create(Box::Orientation::VERTICAL, 2);
		auto playBox = Box::Create(Box::Orientation::VERTICAL, 2);
		playBox->Pack(playSpButton);
		playBox->Pack(playLocalMpButton);
		auto playFrame = Frame::Create("Play");
		playFrame->Add(playBox);
		playFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.2f));

		auto boardSizeBox = Box::Create(Box::Orientation::HORIZONTAL, 5);
		boardSizeScale = Scale::Create(8.0f, 20.0f, 1.0f, Scale::Orientation::HORIZONTAL);
		boardSizeScale->SetValue(15.0f);
		boardSizeScale->SetRequisition(Vector2f(0.0f, ct::WindowWidth * 0.08f));
		boardSizeScale->GetAdjustment()->GetSignal(Adjustment::OnChange)
			.Connect(bind(&MainMenuUi::updateBoardSize, this));
		boardSizeLabel = Label::Create();
		boardSizeLabel->SetRequisition(Vector2f(ct::WindowWidth * 0.05f, 0.0f));
		boardSizeBox->Pack(Label::Create("Size:"), false, false);
		boardSizeBox->Pack(createAlignment(boardSizeScale, Vector2f(0.5f, 0.5f), Vector2f(1.0f, 1.0f)));
		boardSizeBox->Pack(createAlignment(boardSizeLabel, Vector2f(1.0f, 0.5f), Vector2f(0.0f, 0.0f)), false,
			false);

		auto mineCountBox = Box::Create(Box::Orientation::HORIZONTAL, 5);
		mineCountScale = Scale::Create(Range::Orientation::HORIZONTAL);
		mineCountScale->SetIncrements(1.0f, 1.0f);
		mineCountScale->SetRequisition(Vector2f(0.0f, ct::WindowWidth * 0.08f));
		mineCountScale->GetAdjustment()->GetSignal(Adjustment::OnChange)
			.Connect(bind(&MainMenuUi::updateMineCount, this));
		mineCountLabel = Label::Create();
		mineCountLabel->SetRequisition(Vector2f(ct::WindowWidth * 0.05f, 0.0f));
		mineCountBox->Pack(Label::Create("Mines: "), false, false);
		mineCountBox->Pack(createAlignment(mineCountScale, Vector2f(0.5f, 0.5f), Vector2f(1.0f, 1.0f)));
		mineCountBox->Pack(createAlignment(mineCountLabel, Vector2f(1.0f, 0.5f), Vector2f(0.0f, 0.0f)), false,
			false);

		updateBoardSize();

		auto settingsBox = Box::Create(Box::Orientation::VERTICAL, 0);
		settingsBox->Pack(boardSizeBox);
		settingsBox->Pack(mineCountBox);
		auto settingsFrame = Frame::Create("Settings");
		settingsFrame->Add(settingsBox);
		settingsFrame->SetRequisition(Vector2f(0.0f, ct::WindowHeight * 0.15f));

		mainBox->Pack(mMpLabel);
		mainBox->Pack(playFrame);
		mainBox->Pack(settingsFrame);
		mainBox->Pack(exitButton);

		window->Add(createAlignment(mainBox, Vector2f(0.5f, 0.5f), Vector2f(0.7f, 0.7f)));
	}


	void MainMenuUi::updateBoardSize() {
		int boardSize = (int)round(boardSizeScale->GetValue());
		boardSizeLabel->SetText(to_string(boardSize));

		//The last term is because of the padding.
		mineCountScale->SetRange((float) boardSize, (float)(boardSize * boardSize - (4 * 3 * 4 / 2)));
		const float loadFactor = 0.24f;
		mineCountScale->SetValue((float)((int)(boardSize * boardSize * loadFactor)));

		gameSettings.boardSize = boardSize;

		updateMineCount();
	}

	void MainMenuUi::updateMineCount() {
		int mineCount = (int)round(mineCountScale->GetValue());
		mineCountLabel->SetText(to_string(mineCount));

		gameSettings.mineCount = mineCount;

		updateSettingsAction(gameSettings);
	}
}
