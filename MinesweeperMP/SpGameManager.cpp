#include "SpGameManager.h"

namespace mMp
{
	SpGameManager::SpGameManager(int boardSize, int mineCount, Action1P<UiEvent> postUiEventAction)
		: postUiEventAction(postUiEventAction), board(boardSize, mineCount) {
	}

	void SpGameManager::postCommand(Command command) {
		if (command.commandType == Command::CommandType::TileOpen) {
			Board::BoardPoint point(command.tileOpenCommand.line, command.tileOpenCommand.column);
			if (board.isMine(point)) {
				postUiEventAction(UiEvent(UiEvent::GameOverEvent(false)));
			}
			else {
				handleReveal(point);
			}
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
		vector<Board::BoardPoint> revealedPoints = board.reveal(rootPoint);
		for (auto point : revealedPoints) {
			postUiEventAction(
				UiEvent(UiEvent::TileRevealEvent(point.line, point.column, board.getNeighbors(point))));
		}
		if (board.isCompleted()) {
			postUiEventAction(UiEvent(UiEvent::GameOverEvent(true)));
		}
	}
}
