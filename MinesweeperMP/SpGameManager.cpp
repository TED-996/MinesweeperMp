#include "SpGameManager.h"

namespace mMp
{
	SpGameManager::SpGameManager(GameSettings gameSettings, Action1P<UiEvent> postUiEventAction)
		: postUiEventAction(postUiEventAction), board(gameSettings.boardSize, gameSettings.mineCount) {
		gameOver = false;
	}

	void SpGameManager::postCommand(Command command) {
		if (gameOver) {
			return;
		}
		if (command.commandType == Command::CommandType::TileOpen) {
			auto tileOpenCommand = command.tileOpenCommand;
			handleReveal(Board::BoardPoint(tileOpenCommand.line, tileOpenCommand.column));
		}
		if (command.commandType == Command::CommandType::TileFlag) {
			Board::BoardPoint point(command.tileFlagCommand.line, command.tileFlagCommand.column);
			if (board.isRevealed(point)) {
				return;
			}
			board.toggleFlag(point);
			postUiEventAction(UiEvent(UiEvent::TileFlagEvent(point.line, point.column, board.isFlagged(point))));
		}
	}

	void SpGameManager::handleReveal(Board::BoardPoint rootPoint) {
		if (board.isFlagged(rootPoint)) {
			return;
		}
		if (board.isMine(rootPoint)) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(false, 0)));
			gameOver = true;
			return;
		}
		if (board.isRevealed(rootPoint)) {
			handleRevealAround(rootPoint);
			return;
		}
		vector<Board::BoardPoint> revealedPoints = board.reveal(rootPoint);
		for (auto point : revealedPoints) {
			if (board.isFlagged(point)) {
				board.toggleFlag(point);
				postUiEventAction(UiEvent(UiEvent::TileFlagEvent(point.line, point.column, false)));
			}
			postUiEventAction(
				UiEvent(UiEvent::TileRevealEvent(point.line, point.column, board.getNeighbors(point))));
		}
		if (board.isCompleted()) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(true, 0)));
			gameOver = true;
		}
	}

	void SpGameManager::handleRevealAround(Board::BoardPoint rootPoint) {
		int flagsAround = 0;
		int minesAround = 0;
		for (int i = 0; i < 8; i++) {
			auto neighbor = rootPoint.getNeighbor((Direction)i);
			if (board.isFlagged(neighbor)) {
				flagsAround++;
			}
			if (board.isMine(neighbor)) {
				minesAround++;
			}
		}
		if (flagsAround != minesAround) {
			return;
		}

		for (int i = 0; i < 8; i++) {
			auto neighbor = rootPoint.getNeighbor((Direction)i);
			if (board.isValid(neighbor) && !board.isRevealed(neighbor) && !board.isFlagged(neighbor)) {
				handleReveal(neighbor);
			}
		}
	}
}
